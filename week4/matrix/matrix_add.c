#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    int **data;
    int row;
    int col;
}
Matrix1;

typedef struct
{
    int *data;
    int row;
    int col;
}
Matrix2;

// Generate Matrix using first struct
Matrix1 fill_matrix1(int row, int col)
{
    Matrix1 m1;
    m1.row = row;
    m1.col = col;
    m1.data = calloc(row, sizeof(int*));

    int fill_num = 1;
    for (int i = 0; i < row; i++)
    {
        m1.data[i] = calloc(col, sizeof(int));
        for (int j = 0; j < col; j++)
        {
            m1.data[i][j] = fill_num;
            fill_num++;
        }
    }
    return m1;
}

// Generate Matrix using second struct
Matrix2 fill_matrix2(int row, int col)
{
    Matrix2 m2;
    m2.row = row;
    m2.col = col;
    m2.data = calloc(row * col, sizeof(int));

    int fill_num = row * col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int index_curr = (i * col) + j;
            m2.data[index_curr] = fill_num;
            fill_num--;
        }
    }

    return m2;
}

// Matirx addition
Matrix1 cal_sum_matrix(Matrix1 m1, Matrix2 m2)
{
    Matrix1 m_sum;
    m_sum.row = m1.row;
    m_sum.col = m1.col;
    m_sum.data = calloc(m_sum.row, sizeof(int*));

    for (int i = 0; i < m_sum.row; i++)
    {
        m_sum.data[i] = calloc(m_sum.col, sizeof(int));
        for (int j = 0; j < m_sum.col; j++)
        {
            int index_m2 = (i * m_sum.col) + j;
            m_sum.data[i][j] = m1.data[i][j] + m2.data[index_m2];
        }
    }
    return m_sum;
}

// Matirx1 print
void print_matrix1(Matrix1 m1)
{
    printf("The matrix1 is: \n");
    for (int i = 0; i < m1.row; i++)
    {
        for (int j = 0; j < m1.col; j++)
        {
            printf("%d, ", m1.data[i][j]);
        }
        printf("\n");
    }

}
// Matirx2 print
void print_matrix2(Matrix2 m2)
{
    printf("The matrix2 is: \n");
    for (int i = 0; i < m2.row; i++)
    {
        for (int j = 0; j < m2.col; j++)
        {
            int index_curr = (i * m2.col) + j;
            printf("%d, ", m2.data[index_curr]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix1 m)
{
    for (int i = 0; i < m.row; i++)
    {
        free(m.data[i]);
    }
    free(m.data);
}

int main(int argc, char *argv[])
{
    // Check for invalid command line arguments
    if (argc != 3)
    {
        printf("Usage: matrix row and col \n");
        return 1;
    }

    // Convert argument into int
   int row = atoi(argv[1]);
   int col = atoi(argv[2]);
   if (row == 0 || col == 0)
   {
        printf("Please enter valid number of matrix row and col \n");
        return 1;
   }

   // fill_matrix1
   Matrix1 m1 = fill_matrix1(row, col);
   print_matrix1(m1);

   // fill_matrix2
   Matrix2 m2 = fill_matrix2(row, col);
   print_matrix2(m2);

   // sum of two matrices
   Matrix1 m_sum = cal_sum_matrix(m1, m2);
   free(m1.data);
   free(m2.data);

   // print sum
   print_matrix1(m_sum);
   free(m_sum.data);
}