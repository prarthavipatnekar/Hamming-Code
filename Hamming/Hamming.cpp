// Hamming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <armadillo>

using namespace std;
using namespace arma;

int getUserInput()
{
    string dataBits = "";

    
    bool notString = false;
    while (!notString)
    {
        cout << "Enter number of databits: ";
        cin >> dataBits;
        notString = true;
        for (int i = 0; i < dataBits.length() && notString; i++)
        {
            if (isdigit(dataBits[i]) == false)
            {
                notString = false;
            }
        }
    }
    
    return stoi(dataBits);

}



 mat generateXVector(mat g, mat p)
 {
     mat res = p * g;
     res.for_each([](mat::elem_type& val) { val = (int)val % 2;});
     return res;
 }

 vector<int> decToBinary(int n, int len)
 {
     vector<int> binary(len);

     for (int i = len - 1; i >= 0; i--)
     {
         if (n > 0)
         {
             binary[i] = n % 2;
             n = n / 2;
         }
         else
             binary[i] = 0;
     }
     return binary;
 }

 mat generateRMatrix(int p, int d)
 {
     int total = p + d;
     mat r(total,d, fill::zeros);
     for (int i = 0; i < d; i++)
     {
         r(i, i) = 1;
     }
     return r;
}


 mat generateHMatrix(int p, int d)
 {
     int total = p + d;
     mat h(p, total, fill::zeros);
     for (int i = 0; i < p; i++)
     {
         h(i, d + i) = 1;
     }
     int cnt = 3;
     int power = 2;
     vector<int> bin;
     for (int i = d - 1; i >= 0;i--){
         if (pow(2, power) == cnt)
         {
             power++;
             cnt++;
         }
         bin = decToBinary(cnt, p);
         cnt++;
        
         for (int j = 0; j < bin.size(); j++)
         {
             h(j,i) = bin[j];
         }
     }

     return h;
 }

 mat generateGMatrix(int p, int d)
 {
     
     mat g(d,d+p, fill::zeros);
     for (int i = 0; i < d; i++)
     {
         g(i, i) = 1;
     }
     vector<int> bin;

     int cnt = 3;
     int power = 2;

     for (int i = d -1; i >= 0; i--)
     {
         if (pow(2, power) == cnt)
         {
             power++;
             cnt++;
         }
         bin = decToBinary(cnt, p);
         cnt++;
         for (int j = d; j < d + p; j++)
         {
             g(i, j) = bin[j - d];
         }
     }

     return g;
 }

 

 void printBits(int size, mat p)
 {
     cout << "[";
     if (p.is_colvec())
     {
         for (int i = 0; i < size; i++)
         {
             if (i < size - 1)
                 cout << p(i, 0) << " ";
             else
                 cout << p(i, 0) << "]";
         }
     }
     else
     {
         for (int i = 0; i < size; i++)
         {
             if (i < size - 1)
                 cout << p(0, i) << " ";
             else
                 cout << p(0, i) << "]";
         }
     }
     
     cout << endl;
 }
 mat errorCorrection(int p, int d, mat r)
 {
     mat a = r;
     mat H = generateHMatrix(p, d);
     inplace_trans(r);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
     mat z = H * r;
     int cnt = 0;
     
     z.for_each([](mat::elem_type& val) {val = (int)val % 2;});
     cout << "Parity Check:    : ";
     int zRows = z.n_rows;
     printBits(zRows, z);
     for (int i = 0; i < zRows;i++)
     {
         z(i,0 ) = (int)z(i, 0) % 2;
         if (z(i, 0) == 0)
            cnt++;
     }
     if (cnt != zRows)
     {
         bool found = false;
         int col = 0;
         while (!found && col < H.n_cols)
         {
             bool matchSoFar = true;
             int row = 0;
             while ( row < H.n_rows && matchSoFar)
             {
                 if (H(row, col) != z(row, 0))
                     matchSoFar = false;
                 else
                     row++;
             }
             if (row == H.n_rows)
                 found = true;
             else
                 col++;
         }
         //cout << "Error in the bit number: " << col << endl;
         r(col,0) = r(col,0) == 0 ? 1 : 0;


     }
     cout << "Corrected Message: ";
     printBits(p + d, r);

     inplace_trans(r);
     return r;
        
 }

 mat generateError(int total, mat sendingMessage)
 {
     int errorBit = rand() % total;
     mat receivingMessage = sendingMessage;
     if(errorBit - 1 >= 0)
         receivingMessage(0, errorBit - 1) = receivingMessage(0, errorBit - 1) == 0  ? 1 : 0;
     return  receivingMessage;
 }
 int calculateParityNum(int dataBitsNum) {
     int parityNum = 0;
     while (pow(2, parityNum) < dataBitsNum + parityNum + 1) {
         parityNum++;
     }
     return parityNum;
 }

 mat generateDataBits(int dataBitsNum)
 {
     rowvec p(dataBitsNum, fill::zeros);
     for (int i = 0; i < dataBitsNum;i++)
     {
         p(i) = rand() % 2;
     }
     return p;
 }
int main()
{
    srand(time(0));
    while (true) {
        int dataBitsNum = getUserInput();
        int parityNum = 0;
        rowvec p(dataBitsNum, fill::zeros);

        parityNum = calculateParityNum(dataBitsNum);
        p = generateDataBits(dataBitsNum);

        cout << "Message          : ";
        printBits(dataBitsNum, p);


        mat g = generateGMatrix(parityNum, dataBitsNum);

        mat send = generateXVector(g, p);
        cout << "Send Vector      : ";
        printBits(dataBitsNum + parityNum, send);



        //create error in the sending message
        mat receive = generateError(parityNum + dataBitsNum, send);
        cout << "Received Vector  : ";
        printBits(dataBitsNum + parityNum, receive);

        receive = errorCorrection(parityNum, dataBitsNum, receive);

        mat R = generateRMatrix(parityNum, dataBitsNum);
        mat decoded = generateXVector(R, receive);
        cout << "Decoded Message  : ";
        printBits(dataBitsNum, decoded);
    }
   
   
}



