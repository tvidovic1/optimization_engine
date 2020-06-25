#include "Helper.h"
#include "iostream"
#include "math.h"
#include <algorithm>
#include<random>
#include <ctime>

int findIndex(std::vector<int> values, int value)
{

    int index = -1;

    for (int i = 0; i < values.size(); i++)
    {
        if (value == values[i])
        {
            index = i;
        }
    }

    return index;
}

long long int findGreatestCommonDivisor(long long int a, long long int b)
{
    // GCD found
	if (b == 0) return a;

    // GCD not found repeat for a mod b
	return findGreatestCommonDivisor(b, a % b);
}


long long int findGreatestCommonDivisorOfVector(std::vector<long long int> inputs)
{

    // check if inputs is empty
    if (inputs.size() == 0)
    {
        throw std::invalid_argument("The input vector is empty!");
    }

    long long int result = inputs.at(0);
    for (int i = 1; i < inputs.size(); i++)
    {
        result = findGreatestCommonDivisor(inputs.at(i), result);

        if (result == 1)
        {
            return 1;
        }
    }
    return result;
}

long long int findLeastCommonMultiple(std::vector<long long int> inputs)
{
    
	// check if inputs is empty
    if (inputs.size() == 0)
    {
        throw std::invalid_argument("The input vector is empty!");
    }

    //get the GCD of the array
    long long int GCD = findGreatestCommonDivisorOfVector(inputs);

    // array can now safely be divided by GCD to reduce operand size
    for (int i = 0; i < inputs.size(); i++)
    {
        inputs.at(i) = inputs.at(i) / GCD;
    }

    long long int LCM = inputs.at(0);

    //std::cout << "na 0: " << LCM << std::endl;
	for (int i = 1; i < inputs.size(); i++)
	{
        if (findGreatestCommonDivisor(inputs.at(i), LCM) == 0)
        {
            throw std::domain_error("Division by zero");
        }
		LCM = (((inputs.at(i) * LCM)) / (findGreatestCommonDivisor(inputs.at(i), LCM)));
      
	}

    // multiply with GCD again
	return LCM * GCD;
}

int getFirstDigit(int number)
{
    if (number >= 0 && number < 1000) return 0;

    else return number / 1000;

}

int getSecondDigit(int number)
{

    if (number >= 0 && number < 100) return 0;
    else
    {
        return (number - getFirstDigit(number) * 1000) / 100;
    }
}

int getThirdDigit(int number)
{
    if (number < 10) return 0;

    else return (number - getFirstDigit(number) * 1000 - getSecondDigit(number)*100 ) / 10;

}

int getFourthDigit(int number)
{
    if (number < 10) return number;

    else return (number - getFirstDigit(number) * 1000 - getSecondDigit(number) * 100 - getThirdDigit(number) * 10) / 1;

}

bool intervalsOverlap(long long int a1, long long int a2, long long int b1, long long int b2)
{
    if (b1 > a2 || a1 > b2) return false;
    else return true;
}

bool follows(TaskInstance a, TaskInstance b)
{
    return true;
}

void showVectorInt(std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec.at(i) << "  ";
    }

    std::cout << std::endl;

}

void showVector(std::vector<double> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {   
        std::cout << vec.at(i) << "  ";
    }

    std::cout << std::endl;
}

void showMatrix(std::vector<std::vector<double> > matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.at(i).size(); j++)
        {
            std::cout << matrix.at(i).at(j) << "  ";
        }
        std::cout << std::endl << std::endl;
    }
}

std::vector<std::vector<double> > repmat(std::vector<std::vector<double> > mat, int rows, int columns)
{

    int oldRowSize = mat.size();

    int oldColumnSize = mat.at(0).size();

    // replicate rows
    for (int row = 0; row < rows - 1; row++)
    {

        for (int i = 0; i < oldRowSize; i++)
        {

            std::vector<double> matRow = mat.at(i);

            mat.push_back(matRow);
        }
    }

    // replicate columns

    for (int column = 0; column < columns - 1; column++)
    {
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < oldColumnSize; j++)
            {
                mat.at(i).push_back(mat.at(i).at(j));
            }
        }


    }

    return mat;
}

std::vector<std::vector<double>> generateTaskUtilization(double n, double u)
{

    // documentation available online at: https://se.mathworks.com/matlabcentral/fileexchange/9700-random-vectors-with-fixed-sum
    double a = 0;

    double b = 1;

    int m = 1;

    std::random_device rd;

    std::mt19937 gen(rd());

    // Rescale u to a unit cube

    u = (u - n * a) / (b - a);

    // Construct the transition probability table t
    // t[i][j] will be utilized only in the region where j<= i+1

    double k = std::max(std::min(std::floor(u), n - 1), 0.);


    u = std::max(std::min(u, k + 1), k);
    
    std::vector<double> u1;

    std::vector<double> u2;

    for (int i = k; i >= k-n+1; i--)
    {
        u1.push_back(u - (double) i);
    }

    for (int i = k + n; i >= k + 1; i--)
    {
        u2.push_back((double)i - u);
    }
    
    std::vector<std::vector<double>> w;

    for (int i = 0; i < n; i++)
    {
        std::vector<double> newPart;
        w.push_back(newPart);

        for (int j = 0; j < n + 1; j++)
        {
            w.at(i).push_back(0.);
        }
    }

    w[0][1] = std::numeric_limits<double>::max();


    std::vector<std::vector<double>> t;

    for (int i = 0; i < n - 1; i++)
    {
        std::vector<double> newPart;

        t.push_back(newPart);

        for (int j = 0; j < n; j++)
        {
            t.at(i).push_back(0.);
        }
    }

    
    for (int i = 1; i < n; i++)
    {
        std::vector<double> tmp1;
        std::vector<double> tmp2;
        std::vector<double> tmp3;
        std::vector<bool> tmp4;

        std::vector<double> wHelp1;
        std::vector<double> u1Help1;

        for (int j = 1; j <= i + 1; j++)
        {
            wHelp1.push_back(w[i - 1][j]);
        }

        for (int k = 0; k <= i; k++)
        {
            u1Help1.push_back(u1[k]);
        }

        for (int l = 0; l < wHelp1.size(); l++)
        {
            tmp1.push_back((wHelp1[l] * u1Help1[l])/(i+1));
        }


        std::vector<double> wHelp2;
        std::vector<double> u2Help1;

        for (int j = 0; j <= i; j++)
        {
            wHelp2.push_back(w[i - 1][j]);
        }

        for (int k = (n-1)-i; k < n; k++)
        {
            u2Help1.push_back(u2[k]);
        }


        for (int l = 0; l < wHelp2.size(); l++)
        {
            tmp2.push_back((wHelp2[l] * u2Help1[l]) / (i + 1));
        }


        // tmp3
        for (int l = 1; l <= i + 1; l++)
        {
            w[i][l] = tmp1[l - 1] + tmp2[l - 1];
            tmp3.push_back(w[i][l] + DBL_TRUE_MIN);
        }

        //tmp4

        for (int j = 0; j < u1Help1.size(); j++)
        {
            tmp4.push_back(u2Help1[j] > u1Help1[j]);
        }


        for (int j = 0; j <= i; j++)
        {
            t[i - 1][j] = (tmp2[j] / tmp3[j]) * tmp4[j] + (1 - tmp1[j] / tmp3[j]) * (1 - tmp4[j]);
        }

    }

    double v = std::pow(n, 3. / 2) * (w[(n - 1)][k + 1] / std::numeric_limits<double>::max()) * std::pow(b - a, n - 1);

    // Now generate x:

    std::vector<std::vector<double> > x;

    for (int i = 0; i < n; i++)
    {
        std::vector<double> newPart;

        x.push_back(newPart);

        for (int j = 0; j < m; j++)
        {
            x.at(i).push_back(0); // initialize x to all zeros

        }
    }

    if (m == 0) return x; // if 0 simplexes are wanted return immediately

    std::uniform_real_distribution<double> distributionrtrs(0., 1.);

    // For random selection of simplex

    std::vector<std::vector<double> > rt;

    for (int i = 0; i < n - 1; i++)
    {
        std::vector<double> newPart;

        rt.push_back(newPart);

        for (int j = 0; j < m; j++)
        {
            double number = distributionrtrs(gen);

            rt.at(i).push_back(number); // initialize rt with uniform random numbers in [0, 1]

        }
    }

    // For random selection of location in one simplex

    std::vector<std::vector<double> > rs;

    for (int i = 0; i < n - 1; i++)
    {
        std::vector<double> newPart;

        rs.push_back(newPart);

        for (int j = 0; j < m; j++)
        {
            double number = distributionrtrs(gen);

            rs.at(i).push_back(number); // initialize rt with uniform random numbers in [0, 1]

        }
    }

    std::vector <std::vector<double>> s; 

    std::vector<double> newPartOfS;

    newPartOfS.push_back(u);

    s.push_back(newPartOfS);

    s = repmat(s, 1, m);

    std::vector <std::vector<double>> j = { {k} };

    j = repmat( j, 1, m); // For indexing in t table

    // Initial sum is 0

    std::vector<std::vector<double> > sum;

    for (int i = 0; i < 1; i++)
    {
        std::vector<double> newPart;

        sum.push_back(newPart);

        for (int j = 0; j < m; j++)
        {
            sum.at(i).push_back(0); // initialize x to all zeros

        }
    }

    // Initial product is 1

    std::vector<std::vector<double> > product;

    for (int i = 0; i < 1; i++)
    {
        std::vector<double> newPart;

        product.push_back(newPart);

        for (int j = 0; j < m; j++)
        {
            product.at(i).push_back(1); // initialize x to all ones

        }
    }

    // work backwards through the t table

    for (int i = n - 2; i >= 0; i--)
    {
        std::vector<bool> e; // use rt to choose a transition

        for (int rtIndex = 0; rtIndex < rt.at(n - i - 2).size(); rtIndex++)
        {
            e.push_back( rt.at(n - i - 2).at(rtIndex) <= t.at(i).at(j.at(0).at(rtIndex)) );

        }

        // use rs to compute next simplex coordinate
        std::vector<double> sx;

        for (int rtIndex = 0; rtIndex < rs.at(n - i - 2).size(); rtIndex++)
        {
            sx.push_back(pow(rs.at(n - i - 2).at(rtIndex), 1. / (i + 1)));
        }

        // update sum

        for (int rtIndex = 0; rtIndex < rt.at(n - i - 2).size(); rtIndex++)
        {
            sum.at(0).at(rtIndex) = sum.at(0).at(rtIndex) + (1 - sx.at(rtIndex)) * product.at(0).at(rtIndex) * s.at(0).at(rtIndex) / (i + 2);
        }

        // update product

        for (int rtIndex = 0; rtIndex < rt.at(n - i - 2).size(); rtIndex++)
        {
            product.at(0).at(rtIndex) = sx.at(rtIndex) * product.at(0).at(rtIndex);
        }

        // calculate x using simplex coordinates

        for (int xIndex = 0; xIndex < x.at(n - i - 2).size(); xIndex++)
        {
            x.at(n - i - 2).at(xIndex) = sum.at(0).at(xIndex) + product.at(0).at(xIndex) * e.at(xIndex);
        }

        //Transition adjustment

        for (int sAndERowIndex = 0; sAndERowIndex < s.size(); sAndERowIndex++)
        {
            for (int sAndEColumnIndex = 0; sAndEColumnIndex < s.at(0).size(); sAndEColumnIndex++)
            {
                s.at(sAndERowIndex).at(sAndEColumnIndex) = s.at(sAndERowIndex).at(sAndEColumnIndex) - e.at(sAndEColumnIndex);

                j.at(sAndERowIndex).at(sAndEColumnIndex) = j.at(sAndERowIndex).at(sAndEColumnIndex) - e.at(sAndEColumnIndex);
            }
        }
    }


    // Calculate final x

    for (int xIndex = 0; xIndex < x.at(n - 1).size(); xIndex++)
    {
        x.at(n - 1).at(xIndex) = sum.at(0).at(xIndex) + product.at(0).at(xIndex) * s.at(0).at(xIndex);
    }

    //Transpose x:

    std::vector<std::vector<double>> xTransposed;

    for (int i = 0; i < x.at(0).size(); i++)
    {
        xTransposed.push_back(std::vector<double>());

        for (int j = 0; j < x.size(); j++)
        {
            xTransposed.at(i).push_back(x.at(j).at(i));
        }
    }

    // Randomly permute the order in the columns of x and rescale:

    //shuffle the first row
    std::random_shuffle(xTransposed.at(0).begin(), xTransposed.at(0).end());

    //shuffle other rows
    for (int xSize = 0; xSize < xTransposed.size(); xSize++)
    {
        std::random_shuffle(xTransposed.at(xSize).begin(), xTransposed.at(xSize).end());

    }

    return xTransposed;

}


int roulleteWheelSelecetion(std::vector<double> probabilities)
{
    // check if input is empty
    if (probabilities.size() == 0)
    {
        throw std::invalid_argument("The input vector is empty!");
    }

    // starting value
    double totalSumOfProbabilities = 0.0;


    // update total sum
    for (int i = 0; i < probabilities.size(); i++)
    {
        totalSumOfProbabilities += probabilities[i];
    }
    

    double sum = probabilities[0];
    int index = 0;


    // generate a random number in range [0, totalSumOfProbailities]
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distribution(0., totalSumOfProbabilities);

    double number = distribution(gen);


    // return the index of where on the roulette wheel it landed
    while (sum < number)
    {
        index += 1;

        sum += probabilities[index];
        
    }

    return index;
}

bool setsIntersect(std::set<int> a, std::set<int> b)
{
    std::vector<int> common_data;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(),
        std::back_inserter(common_data));

    if (common_data.size() == 0) return false; // no data in set intersection, return false
    else return true;
}

bool canCommunicate(TaskInstance producer, TaskInstance consumer)
{
    // Determine DataWrite Interval of producer
    long long int startOfProducerDataWriteInterval = producer.getAbsoluteReleaseTime() + producer.getTask().getWorstCaseExecutionTime();

    long long int endOfProducerDataWriteInterval = (producer.getAbsoluteDeadline() - producer.getTask().getWorstCaseExecutionTime()) + producer.getTask().getPeriod();

    // Determine DataRead Interval of consumer
    long long int startOfConsumerDataReadInterval = consumer.getAbsoluteReleaseTime();

    long long int endOfConsumerDataRadInterval = consumer.getAbsoluteDeadline() - consumer.getTask().getWorstCaseExecutionTime();

    // If the DataWrite and DataRead Intervals overlap the two instances can potentially communicate
    return intervalsOverlap(startOfProducerDataWriteInterval, endOfProducerDataWriteInterval, startOfConsumerDataReadInterval, endOfConsumerDataRadInterval);

}