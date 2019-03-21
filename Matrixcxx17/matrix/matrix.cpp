#pragma once

#define DEBUG
#define MEMMANAGER
#include <iostream>
#include <map>

# ifdef DEBUG
int globtest = 0;
# endif

namespace MatrixSpace
{

	class MatrixError
	{
	public:

		MatrixError();

		MatrixError(const char *str);

		MatrixError(std::string &str);

		MatrixError(const MatrixError &rhs);

		const char *what() const;

	protected:

		std::string msg;
	};

	/*
	 * MatrixCalculateError:
	 *
	 * 当Matrix二元运算不匹配时，发生该Exception
	 * 使用MatrixCalculateError("Exception Descript...")产生一个Exception
	 */
	typedef MatrixError MatrixCalculateError;

	/*
	 * MatrixReferenceError:
	 *
	 * 当访问超过了Matrix的行大小或者内存管理对应的MatrixReference缺失时，发生此错误
	 * 使用MatrixReferenceError("Exception Descript...")产生一个Exception
	 */
	typedef MatrixError MatrixReferenceError;

	/*
	 * MatrixConflictError:
	 *
	 * 当已经添加对应的内存管理时，发生此错误
	 * 使用MatrixConflictError("Exception Descript...")产生一个Exception
	 */
	typedef MatrixError MatrixConflictError;

	/*
	 * Matrix<MatrixType>:
	 *
	 * 一个泛型的矩阵类，支持加减运算
	 * 如果你定义了预编译宏 SAFEMATRIX 类会帮你检查可能的错误，否则它会相信你的所有举止都是聪明的。
	 *
	 * Unsafe Matrix:
	 * 注意数组的初始化采用了new，确保你的new和delete配对使用
	 * 注意数组的加减运算采用了new，请不要使用链运算，这会导致内存泄漏
	 *
	 * Safe Matrix:
	 * 防止数组访问越界
	 */

	class MemoryManagable
	{
	public:
		MemoryManagable() {}
		virtual ~MemoryManagable() {}
	};

	template <typename MatrixType>
	class Matrix: public MemoryManagable
	{
	private:

		int row, col, rmc;

		MatrixType *aloc_array;

		template <typename MtxType>
		friend std::ostream &operator<< (std::ostream &os, Matrix<MtxType> const &out_mat);

	public:
		/*
		 * 默认构造函数
		 *
		 * 此时，矩阵的行列值均为0,数组指针为nullptr
		 */
		Matrix();

		/*
		 * 带有行列输入的构造函数
		 * @size_row: 行的大小
		 * @size_col: 列的大小
		 *
		 * 此时，矩阵的行列值为(size_row, size_col)
		 * 数组恰好支持[0 ~ (size_row - 1)][0 ~ (size_col - 1)]的访问
		 * ...
		 */
		Matrix(int const size_row, int const size_col);

		/*
		 * 矩阵的析构函数
		 *
		 * 会废弃所有已申请的内存
		 */
		~Matrix();

		/*
		 * []符号重载
		 *
		 * 假设你的矩阵实例是Mat，使用Mat[x][y]访问第x行第y列的元素
		 * x在0 ~ (size_row - 1)之间，y在0 ~ (size_col - 1)之间
		 */
		inline MatrixType *operator[] (int const sel_row) const;

		/*
		 * +符号重载
		 * @arg1: Matrix<MatrixType>
		 * @arg2: Matrix<MatrixType>
		 * @res: Matrix<MatrixType>*
		 *
		 * 假设你的矩阵实例是A, B，使用一个指针接受运算结果C = A + B
		 * 使用delete C，结束输出结果的生命周期
		 * 要求A和B的行列大小相同
		 */
		Matrix<MatrixType> *operator+ (Matrix<MatrixType> const &right_mat) const;

		/*
		 * -符号重载
		 * @arg1: Matrix<MatrixType>
		 * @arg2: Matrix<MatrixType>
		 * @res: Matrix<MatrixType>*
		 *
		 * 假设你的矩阵实例是A, B，使用一个指针接受运算结果C = A - B
		 * 使用delete C，结束输出结果的生命周期
		 * 要求A和B的行列大小相同
		 */
		Matrix<MatrixType> *operator- (Matrix<MatrixType> const &right_mat) const;

		/*
		 * =符号重载
		 * @arg1: Matrix<MatrixType>
		 *
		 * 完成赋值的逻辑检查
		 */
		const Matrix<MatrixType> operator= (Matrix<MatrixType> const &right_mat);

		/*
		 * initfs
		 *
		 * 根据矩阵初始化的row和col依行列顺序读入MatrixType类型的元素.
		 */
		void initfs();
	};
}


class MemoryManager
{
private:
	std::map<MatrixSpace::MemoryManagable*, bool> mem_maps;
public:
	void addToMap(MatrixSpace::MemoryManagable* mat_p)
	{
		if (mem_maps.count(mat_p)) {
			throw std::domain_error("This pointer already registered in memory manager!!");
		}
		mem_maps[mat_p] = true;
		return ;
	}
	void deleteFromMap(MatrixSpace::MemoryManagable* mat_p)
	{
		if (!mem_maps.count(mat_p)) {
			throw std::out_of_range("This pointer is not in memory manager now..");
		}
		try {
			delete mat_p;
			mem_maps.erase(mat_p);
		} catch (...) {
			throw ;
		}
		return ;
	}
	void clearMap()
	{
		for (auto node : mem_maps) {
			try {
				delete node.first;
			} catch (...) {
				throw ;
			}
		}
		mem_maps.clear();
		return ;
	}
} mem_manager;

/*
 * SafeMatrix
 *
 * 在一定程度上保证安全性
 */
namespace MatrixSpace
{
	/*
 * MatrixError
 *
 * 矩阵Exceptions的实现
 */

	MatrixError::MatrixError()
	{
	}

	MatrixError::MatrixError(const char *str)
	{
		msg = std::string(str);
	}

	MatrixError::MatrixError(std::string &str)
	{
		msg = str;
	}

	MatrixError::MatrixError(const MatrixError &rhs)
	{
		msg = rhs.msg;
	}

	const char *MatrixError::what() const
	{
		return msg.c_str();
	}

	template <typename MT>
	inline std::ostream &operator<< (std::ostream &out_s, Matrix <MT> const &out_mat)
	{
		for (int i = 0; i < out_mat.row; i++) {
			if (i != 0)
				out_s << '\n';
			for (int j = 0; j < out_mat.col; j++) {
				if (j != 0)
					out_s << ' ';
				out_s << out_mat[i][j];
			}
		}
		return out_s;
	}

	template <typename MT>
	Matrix <MT>::Matrix()
	{
		aloc_array = nullptr;
		row = col = 0;
	}

	template <typename MT>
	Matrix <MT>::Matrix(int const size_row, int const size_col)
	{
		try {
			rmc = size_row * size_col;
			aloc_array = new MT[rmc];
			row = size_row;
			col = size_col;
# ifdef DEBUG
			std::cout << reinterpret_cast<unsigned long long>(aloc_array) << " allocated" << std::endl;
			globtest++;
# endif
		}
		catch (...) {
			throw;
		}
	}

	template <typename MT>
	Matrix <MT>::~Matrix()
	{
# ifdef DEBUG
		std::cout << reinterpret_cast<unsigned long long>(aloc_array) << " freed" << std::endl;
		globtest--;
# endif
		if (aloc_array != nullptr)
			delete[] aloc_array;
		aloc_array = nullptr;
		rmc = row = col = 0;
	}

	template <typename MT>
	inline MT *Matrix<MT>::operator[] (int const sel_row) const
	{
		if (sel_row > row)
			throw MatrixReferenceError("out of row");
		return aloc_array + sel_row * col;
	}

	template <typename MT>
	Matrix <MT> *Matrix<MT>::operator+ (Matrix <MT> const &right_mat) const
	{
		if ((this->row != right_mat.row) || (this->col != right_mat.col)) {	
			throw MatrixCalculateError("this matrix is not able to calculate with right matrix");
		}

		Matrix <MT> *res_mat = new Matrix <MT>(row, col);

# ifdef MEMMANAGER
		mem_manager.addToMap(res_mat);
# endif

		for (int i = 0; i < rmc; i++) {
			res_mat->aloc_array[i] = aloc_array[i] + right_mat.aloc_array[i];
		}
		return res_mat;
	}

	template <typename MT>
	Matrix <MT> *Matrix<MT>::operator- (Matrix <MT> const &right_mat) const
	{
		if ((this->row != right_mat.row) || (this->col != right_mat.col)) {
			throw MatrixCalculateError("this matrix is not able to calculate with right matrix");
		}

		Matrix <MT> *res_mat = new Matrix <MT>(row, col);
		
# ifdef MEMMANAGER
		mem_manager.addToMap(res_mat);
# endif
		
		for (int i = 0; i < rmc; i++) {
			res_mat->aloc_array[i] = aloc_array[i] - right_mat.aloc_array[i];
		}
		return res_mat;
	}

	template <typename MT>
	const Matrix<MT> Matrix<MT>::operator= (Matrix<MT> const &right_mat)
	{
		// 检查自赋值
		if (this != &right_mat) {
			// 检查aloc_array问题
			if (aloc_array != nullptr && rmc != right_mat.rmc) {
# ifdef DEBUG
				std::cout << reinterpret_cast<unsigned long long>(aloc_array) << " freed" << std::endl;
				globtest--;
# endif
# ifdef MEMMANAGER
				mem_manager.deleteFromMap(this);
# else
				delete[] aloc_array;
				aloc_array = nullptr;
# endif
			}
			if (aloc_array == nullptr) {
				aloc_array = new MT[right_mat.rmc];
# ifdef DEBUG
				std::cout << reinterpret_cast<unsigned long long>(aloc_array) << " allocated" << std::endl;
				globtest++;
# endif
			}
			rmc = right_mat.rmc;
			row = right_mat.row;
			col = right_mat.col;
			memcpy(aloc_array, right_mat.aloc_array, sizeof(MT) * right_mat.rmc);
		}
		return *this;
	}

	//init from stream
	template <typename MT>
	void Matrix<MT>::initfs()
	{
		using std::cin;

		for (int i = 0; i < rmc; i++) {
			cin >> aloc_array[i];
			if (!cin)
				aloc_array[i] = MT();
		}
		return;
	}
}


using namespace MatrixSpace;



int main()
{
	std::ios::sync_with_stdio(false);
	using std::cout;
	using std::endl;

	Matrix <int> *A = new Matrix <int>(4, 5);
	mem_manager.addToMap(A);
	Matrix <int> *B = new Matrix <int>(4, 5);
	mem_manager.addToMap(B);

	cout << "Please input a Matrix <int> (4 * 5)" << endl;
	A->initfs();

	cout << "Please input a Matrix <int> (4 * 5)" << endl;
	B->initfs();

	(*A)[0][0] = 123;
	Matrix <int> *C = (*((*A) + (*B))) + (*A);
	cout << "A+B:" << endl << *C << endl;
	// delete C;
	C = nullptr;

	C = (*A) - (*B);
	cout << "A-B:" << endl << *C << endl;

	C = nullptr;
	A = nullptr;
	B = nullptr;

# ifdef MEMMANAGER
	mem_manager.clearMap();
# endif

# ifdef DEBUG
	cout << globtest << endl;
# endif
	return 0;
}

/*
0 0 1 0 5
1 2 3 4 2
1 2 2 2 2
3 3 3 3 3

5 4 3 2 1
1 2 3 4 2
3 1 2 4 5
3 1 2 4 5

0 0 1 0 5
1 2 3 4 2
1 2 2 2 2
3 3 3 3 3

5 4 3 2
1 2 3 4
3 1 2 4
3 1 2 4


6509400 allocated
6532440 allocated
Please input a Matrix <int> (4 * 5)
0 0 1 0 5
1 2 3 4 2
1 2 2 2 2
3 3 3 3 3
Please input a Matrix <int> (4 * 5)

5 4 3 2 1
1 2 3 4 2
3 1 2 4 5
3 1 2 4 5
6548784 allocated
6563048 allocated
A+B:
251 4 5 2 11
3 6 9 12 6
5 5 6 8 9
9 7 8 10 11
6563240 allocated
A-B:
118 -4 -2 -2 4
0 0 0 0 0
-2 1 0 -2 -3
0 2 1 -1 -2
6548784 freed
6509400 freed
6532440 freed
6563048 freed
6563240 freed
0
*/