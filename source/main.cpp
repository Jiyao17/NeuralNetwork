
#include<iostream>
//#include "matrix.hpp"
#include "utils.hpp"
#include "softmax.hpp"

int main()
{
	using namespace std;
	typedef double scalar;

	// training configs
	constexpr size_t DATASET_LEN = 600;
	constexpr size_t TEST_SET_LEN = 1000;
	constexpr size_t BATCH_SIZE = 15;
	constexpr size_t EPOCH = 100;
	constexpr double lr = 0.05;

	// dataset configs
	string trainSetPath = "./MNIST/mnist_train.csv";
	string testSetPath = "./MNIST/mnist_train.csv";
	MNISTDATA<scalar> dataset(trainSetPath, testSetPath, BATCH_SIZE);
	Matrix<scalar>* X = new Matrix<scalar>[BATCH_SIZE];
	Matrix<scalar>* Tag = new Matrix<double>[BATCH_SIZE];
	for (size_t i = 0; i < BATCH_SIZE; i++)
	{
		X[i].resize(1, 28 * 28);
		Tag[i].resize(1, 1);
	}

	SoftmaxNet<scalar> softmax(28 * 28, 10, 1, 0);
	for (size_t i = 0; i < EPOCH; i++)
	{
		//softmax.importNet("softmax.txt");

		for (rsize_t j = 0; j < DATASET_LEN / BATCH_SIZE; j++)
		{
			//cout << "learning batch: " << j << endl;
			// read training data into X, tag in to Tag
			dataset.dataSetGen(X, Tag, 0);

			softmax.train(X, Tag, BATCH_SIZE, lr);
		}

		size_t count = 0;
		for (rsize_t j = 0; j < TEST_SET_LEN / BATCH_SIZE; j++)
		{
			//cout << "learning batch: " << j << endl;
			dataset.dataSetGen(X, Tag, 1);
			for (size_t k = 0; k < BATCH_SIZE; k++)
			{
				if (Tag[k][0][0] == softmax.eval(X[k]))
					count++;
			}
		}

		cout << "accuracy for epoch " << i << ": " << count / 1000.0 << endl;
	}

	softmax.exportNet("softmax.txt");


	// reset training data
	//dataset.reset(0);
	// reset test data
	dataset.reset(1);


	system("pause");
	return 0;
}


/*







typedef double scalar;
	constexpr size_t INPUT_LEN = 3;
	constexpr size_t BATCH_SIZE = 5;
	// train set config, generate training data in [-scope, +scope]
	constexpr scalar X_SCOPE = 2;
	constexpr scalar NOISE_SCOPE = 1;

	using namespace std;
	typedef Matrix<scalar> Matrix;


	Matrix::Mat M({ { 1.8, -2.2, -0.4 } });
	Matrix w(M);
	w.reshape(INPUT_LEN, 1);
	scalar b = 3.3;

	Matrix X[BATCH_SIZE];
	Matrix Y[BATCH_SIZE];
	LRTS<scalar> ts(w, X_SCOPE, b, NOISE_SCOPE, BATCH_SIZE);

	LinearReg<scalar> net(INPUT_LEN);

	for (size_t epoch = 0; epoch < 10; epoch++)
	{
		for (size_t i = 0; i < 100; i++)
		{
			ts.trainSetGen(X, Y);

			net.train(X, Y, BATCH_SIZE, 0.2);
		}
	}

	cout << net._w;
	cout << net._b;

	system("pause");
	return 0;


Matrix<double> M(3, 4, 2);
	Matrix<double> M1(4, 2, 3);

	cout << M;
	M *= 2;
	cout << M;
	M += 1;
	cout << M;
	M -= 1;
	cout << M;
	M = M - 1;
	cout << M;
	M = M + 1;
	cout << M;
	M = M * 2;
	cout << M;

//ifstream fin("random_narmal.txt");
	double random[RANDOM_SET_LENGTH];

	for (rsize_t i = 0; i < RANDOM_SET_LENGTH; i++)
	{
		double r0 = rand() % 10000 / 10000.0;
		int r1 = rand() % 2 ? -1 : 1;

		random[i] = r0  * r1;
	}

*/


/*
class test
{
	int* _t;
	int len;
public:
	explicit test()
	{
		_t = nullptr;
		len = 0;
		cout << "default constructor called." << endl;
	}

	explicit test(int a)
	{
		len = a;
		_t = new int[len];
		cout << "constructor called." << endl;
	}

	explicit test(const test &t)
	{
		len = t.len;
		_t = new int[len];
		cout << "copy constructor called." << endl;
	}

	test& operator*=(test& t)
	{
		_t[0] = 1;
		len = 1;

		cout << "operater *= called" << endl;
		return *this;
	}

	test& operator=(const test& t)
	{
		delete[] _t;
		int size = t.len;
		_t = new int[t.len];
		_t[0] = t._t[0];
		len = t.len;

		cout << "operater = called" << endl;
		return (*this);
	}

};







test t1(5);
	test t2(3);
	test t3(t1);
	cout << endl;
	test t4 = t2;
	cout << endl;
	t4 = t1;
	cout << endl;
	test t5 = t3 * t4;
	cout << endl;
	test t6 = 2;
	test t7 = test(1);
	cout << endl;
	t7 = t6 * t7;

void f()
{
	Vector<int> v(3, 1);
	std::vector<int> b(3, 2);
	v[1] = 0;
	Vector<int> c = v;
}

int main()
{
	f();

	return 0;
}
	typedef std::shared_ptr<int> vector;
	int* a = new int[3];
	vector v(a);

	v.operator[](1) = 1;

	std::vector<double> v0({ 1, 2 });
	std::vector<double> v1({ 3, 0 });
	std::vector<std::vector<double>> m({ v0, v1 });
	Matrix<double> M1(m);

	auto M2 = M1;
	auto M = M1 * M2;

	return 0;
*/