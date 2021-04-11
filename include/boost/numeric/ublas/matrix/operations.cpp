#include<bits/stdc++.h>
#include <new>
#include <climits>
using namespace std;

/*
A = zeros(3,2);                                                                    done
C = A+B, C = 2*A, etc. for elementwise matrix operations                           done
C = A*B for matrix multiplication                                                  done
C = A' for matrix transposition                                                    done
A==B for elementwise comparision                                                   done
c = A[3] for accessing elements with a single zero-based index                          
c = A(3,2) or A(3,5) = c for accessing elements with a two zero-based indices      done
C = A(1:2,1:3) to generate a matrix instance that contains data of A referenced by the ranges 1:2 and 1:3
*/

template <typename T>
class mat
{
    public:
    int rows,cols;
    T** matrix;

    mat(int x, int y)
    {
        rows=x, cols=y;
        matrix = new T*[rows];
        for (int i = 0; i < rows; ++i)
        matrix[i] = new T[cols];
        
        for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j)
        matrix[i][j]=0;
    }

    void display()
    {
        for(int i=0;i<rows;++i)
        {
            for(int j=0;j<cols;++j)
            cout<<matrix[i][j]<<" ";
            cout<<"\n";
        }
        cout<<"\n";
    }

    mat<T> zeros(int m,int n){
       mat<T> res(m,n);
       for(int i=0;i<m;i++){
         for(int j=0;j<n;j++){
            res.matrix[i][j]=0;
         }
       }
       return res;
    }
    mat<T> transpose()
    {
        mat<T> res(cols,rows);

        for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j)
        res.matrix[j][i]=matrix[i][j];

        return res;
    } 
 
    mat<T> scalarmult(int k){
      mat<T> res(rows,cols);
       for(int i=0;i<rows;++i)
            for(int j=0;j<cols;++j){
                res.matrix[i][j]=k*(matrix[i][j]);
            }
            return res;
    }
    
     mat<T> scalardiv(int k){
      mat<T> res(rows,cols);
       for(int i=0;i<rows;++i)
            for(int j=0;j<cols;++j){
                res.matrix[i][j]=(matrix[i][j])/(k*1.0);
            }
            return res;
    }
    
    
    int indexelement(int i,int j){
    if(i>=rows || i<=0) return -1;
    else if(j>=cols || j<=0) return -1;
    else{
          return(matrix[i][j]);
       }
       return 0;
    }
    
    void setindexelement(int i,int j,float value){
    if(i>=rows || i<=0) return ;
    else if(j>=cols || j<=0) return ;
    else{
          matrix[i][j]=value;
       }
       
    }
    
    bool elementcomp(mat<T>m){
        if(m.rows==rows && m.cols==cols) {
            for(int i=0;i<m.rows;i++){
               for(int j=0;j<m.cols;j++){
                  if(m.matrix[i][j]!=matrix[i][j]){
                     return false;
                  }
               }
            }
        }
        else{
        
          return false;
        }
        return true;
    }
    
    void size(){
       cout<<"rows:"<<rows<<" "<<"columns:"<<cols<<endl;
    }
    
    mat<T> operator +(mat<T> m)
    {
        mat<T> res(rows,cols);
        
        if(m.rows!=rows or m.cols!=cols)
        cout<<"Dimensions do not match!!!\n";

        for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j)
        res.matrix[i][j] = matrix[i][j] + m.matrix[i][j];

        return res;
    }

    mat<T> operator -(mat<T> m)
    {
        mat<T> res(rows,cols);
        
        if(m.rows!=rows or m.cols!=cols)
        cout<<"Dimensions do not match!!!\n";

        for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j)
        res.matrix[i][j] = matrix[i][j] - m.matrix[i][j];

        return res;
    }
    
    mat<T> operator *(mat<T> m)
    {
        mat<T> res(rows,m.cols);
        
        if(m.rows!=cols)
        cout<<"Dimensions do not match!!!\n";
        else   
        {
            for(int i=0;i<rows;++i)
            for(int j=0;j<m.cols;++j)
            {
                for(int k=0;k<cols;++k)
                res.matrix[i][j] += matrix[i][k]*(m.matrix[k][j]);
            }
        }

        return res;
    }
    
    /* 3 operations --> finding A(:,k) , R(1:k-1,k) , Q(:,1:k-1)
     k=k+1
     R(1:k-1,k) = Q(:,1:k-1)' * A(:,k);
    v = A(:,k) - Q(:,1:k-1) * R(1:k-1,k);
    R(k,k) = norm(v);
    Q(:,k) = v / R(k,k); */
    
    // operation1 --> A(:,k) returning kth column(column no's start from 0)
    mat<T> operation1(int k){
        mat<T> res(rows,1);
        for(int i=0;i<rows;++i){
          res.matrix[i][0]=matrix[i][k];
        }
        return res;
    }
    
    // operation2 --> Q(:,1:k-1) all the columns from 0 to k-1
    mat<T> operation2(int k){
        k=k+1;
        mat<T> res(rows,k);
         
        int x=0;
        for(int i=0;i<=k;i++){
          for(int j=0;j<rows;j++){
                res.matrix[j][i]=matrix[j][i];
             }
          }
       
        return res;
    }
    
    // operation3 --> R(1:k-1,k) 1 to k-1 rows and kth column
    
    mat<T> operation3(int k){
       
        mat<T> res(k,1);
        
        for(int i=0;i<k;i++){
          
             res.matrix[i][0]=matrix[i][k];
             
        }
        return res;
    }
    
    float norm(){
      int sum=0;
      for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
          sum+=(matrix[i][j]*matrix[i][j]);
        }
      }
      return sqrt(sum);
    }
    
    
};
int main(){
   mat<int> a(3,4), b(3,4), c(3,4);
   // zero matrices
   a.zeros(3,4);
   a.display();
   for(int i=0;i<3;++i)
    for(int j=0;j<4;++j){
        a.matrix[i][j]=(i+1)*3+j;
        b.matrix[i][j]=i*3+j;
    }
    a.display();
    b.display();
    // addition
    c = a+b;
    c.display();
    // scalar multiplication
    c=a.scalarmult(2);
    c.display();
    mat<int> d(4,3);
    // transpose
    d=c.transpose();
    d.display();
    // element comparision
    if(d.elementcomp(c.transpose())) cout<<"equal matrices"<<endl;
    else cout<<"unequal matrices"<<endl;
    // matrix size
    d.size();
    // access index element
    cout<<"Element: "<<d.indexelement(1,2)<<endl;
    // get kth column
    (d.operation1(2)).display();
    // operation2
    (d.operation2(2)).display();
    // operation3
    
    (d.operation3(2)).display();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   
}
