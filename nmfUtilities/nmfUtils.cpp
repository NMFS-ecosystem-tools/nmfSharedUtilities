
/**
 @file nmfUtils.cpp
 @author rklasky
 @copyright 2017 NOAA - National Marine Fisheries Service
 @brief
 @date Nov 29, 2016
*/

#include <ctime>
#include <fstream>
#include "nmfUtils.h"
#include "nmfConstants.h"
#include "nmfLogger.h"



namespace nmfUtils {



std::chrono::time_point<std::chrono::high_resolution_clock>
startTimer()
{
    return std::chrono::high_resolution_clock::now();
    //return val;
}

std::string
elapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock> startTime)
{
    std::string elapsedTimeStr = "";
    char buffer[50];

    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTimeMSec = std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count();

    if (elapsedTimeMSec >= 60000) {
        sprintf(buffer,"%6.1f",elapsedTimeMSec/60000.0);
        elapsedTimeStr = std::string(buffer) + " minute(s)";
    } else if (elapsedTimeMSec >= 1000) {
        sprintf(buffer,"%6.1f",elapsedTimeMSec/1000.0);
        elapsedTimeStr = std::string(buffer) + " second(s)";
    } else {
        elapsedTimeStr = std::to_string(elapsedTimeMSec) + " millisecond(s)";
    }
    return elapsedTimeStr;
}

void printError(const std::string msg, const std::string errorMsg)
{
    std::cout << "\nError: " << errorMsg << std::endl;
    std::cout << msg << std::endl;
}

void printMsg(std::string msg) {
    std::cout << msg << std::endl;
}

void printMapPair(const std::pair<std::string, std::vector<std::string> > &pair) {
    std::cout << "Key: " << pair.first << std::endl;
    copy(pair.second.begin(), pair.second.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}

void printMap(const std::string name, const std::map<std::string, std::vector<std::string> > &dataMap) {
    std::cout << "Map: " << name << std::endl;
    std::for_each(dataMap.begin(), dataMap.end(), printMapPair);
}

void printMatrix(const std::string &name,
        const boost::numeric::ublas::matrix<double> &mat,
        const int width,
        const int precision) {
    std::cout << "\n" << name << " (" << mat.size1() << "x" << mat.size2()
            << ")" << std::endl;
    for (unsigned i = 0; i < mat.size1(); ++i) {
        std::cout << "  ";
        for (unsigned j = 0; j < mat.size2(); ++j) {
            std::cout << std::setw(width)
                      << std::setprecision(precision)
                      << std::fixed << mat(i, j) << "  ";
        }
        std::cout << std::endl;
    }
}

/*
 * returns sum of all items in the passed patrix
 */
double matrixSum(const boost::numeric::ublas::matrix<double> &mat) {
    return sum(prod(boost::numeric::ublas::scalar_vector<double>(mat.size1()), mat));
}

double vectorSum(const boost::numeric::ublas::vector<double> &vec) {
    return sum(vec);
}



void print3DArray(
        const std::string &name,
        const std::vector<int> &dimensions,
        const Boost3DArrayDouble &array,
        const int &width,
        const int &precision)
{
    int imax = dimensions[0];
    int jmax = dimensions[1];
    int kmax = dimensions[2];

    std::cout <<  name.c_str() << " (" << imax << "x" << jmax << "x" << kmax << "):\n" << std::endl;
    for (int i = 0; i < imax; ++i) {
        for (int j = 0; j < jmax; ++j) {
            for (int k = 0; k < kmax; ++k) {
                std::cout << std::fixed << std::setw(width) << std::setprecision(precision) << array[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void print4DArray(
        const std::string &name,
        const std::vector<int> &dimensions,
        const Boost4DArrayDouble &array)
{
    int imax = dimensions[0];
    int jmax = dimensions[1];
    int kmax = dimensions[2];
    int lmax = dimensions[3];

    std::cout << name.c_str() << " (" << imax << "x" << jmax << "x" << kmax << "x" << lmax
            << "):\n" << std::endl;
    for (int i = 0; i < imax; ++i) {
        for (int j = 0; j < jmax; ++j) {
            for (int k = 0; k < kmax; ++k) {
                for (int l = 0; l < lmax; ++l) {
                    std::cout << array[i][j][k][l] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void printVector(const std::string &name,
        const boost::numeric::ublas::vector<std::string> &vec) {
    std::cout << "\n" << name << ": " << vec.size() << std::endl;
    for (unsigned i = 0; i < vec.size(); ++i) {
        std::cout << "| ";
        std::cout << std::setw(30) << vec(i) << " | ";
        std::cout << std::endl;
    }
}

void printVector(const std::string &name,
                 const std::vector<std::string> &vec)
{
    std::cout << "\n" << name << ": " << vec.size() << std::endl;
    for (unsigned i = 0; i < vec.size(); ++i) {
        std::cout << "| ";
        std::cout << std::setw(4) << vec[i] << " | ";
        std::cout << std::endl;
    }
}

void printVector(const std::string &name,
        const boost::numeric::ublas::vector<double> &vec) {
    std::cout << "\n" << name << ": " << vec.size() << std::endl;
    for (unsigned i = 0; i < vec.size(); ++i) {
        std::cout << "| ";
        std::cout << std::setw(4) << vec(i) << " | ";
        std::cout << std::endl;
    }
}

void initialize(boost::numeric::ublas::vector<std::string> &vec, const int &nrows) {
    vec.resize(nrows);
    vec.clear();
}
void initialize(boost::numeric::ublas::vector<int> &vec, const int &nrows) {
    vec.resize(nrows);
    vec.clear();
}
void initialize(boost::numeric::ublas::vector<double> &vec, const int &nrows) {
    vec.resize(nrows);
    vec.clear();
}
void initialize(boost::numeric::ublas::matrix<int> &mat,
                const int &nrows,
                const int &ncols)
{
    mat.resize(nrows,ncols,false);
    mat.clear();
}
void initialize(boost::numeric::ublas::matrix<double> &mat,
                const int &nrows,
                const int &ncols)
{
    mat.resize(nrows,ncols,false);
    mat.clear();
}
void initialize(Boost3DArrayDouble &array3d)
{
    for (unsigned int i=0; i<array3d.shape()[0]; ++i)
        for (unsigned int j=0; j<array3d.shape()[1]; ++j)
            for (unsigned int k=0; k<array3d.shape()[2]; ++k)
                array3d[i][j][k] = 0.0;
}
void initialize(Boost4DArrayDouble &array4d)
{
    for (unsigned int i=0; i<array4d.shape()[0]; ++i)
        for (unsigned int j=0; j<array4d.shape()[1]; ++j)
            for (unsigned int k=0; k<array4d.shape()[2]; ++k)
                for (unsigned int l=0; l<array4d.shape()[3]; ++l)
                    array4d[i][j][k][l] = 0.0;
}
void initialize(Boost5DArrayDouble &array5d)
{
    for (unsigned int i=0; i<array5d.shape()[0]; ++i)
        for (unsigned int j=0; j<array5d.shape()[1]; ++j)
            for (unsigned int k=0; k<array5d.shape()[2]; ++k)
                for (unsigned int l=0; l<array5d.shape()[3]; ++l)
                    for (unsigned int m=0; m<array5d.shape()[4]; ++m)
                        array5d[i][j][k][l][m] = 0.0;
}

double maxMatrixValue(boost::numeric::ublas::matrix<double> &mat, bool roundOff=false)
{
    // find largest value in mat
    double maxVal = 0.0;
    double val = 0.0;
    for (boost::numeric::ublas::matrix<double>::iterator1 it1 =
            mat.begin1(); it1 != mat.end1(); ++it1) {
        for (boost::numeric::ublas::matrix<double>::iterator2 it2 = it1.begin();
                it2 != it1.end(); ++it2) {
            val = *it2;
            if (val > maxVal) {
                maxVal = val;
            }
        }
    }
    if (maxVal > 1.0) {
        if (roundOff) {
            int numDigits = int(log10(maxVal) + 1);
            int firstDigit = int((maxVal / pow(10.0, numDigits - 1)) + 0.5);
            maxVal = firstDigit * pow(10.0, numDigits - 1);
        }
    } else {
        maxVal = 1.0;
    }
    return maxVal;

}

/*
 * Returns a random number between the passed limits: [lowerLimit,upperLimit)
 * If seed < 0, no seed is used and the algorithm is stochastic.
 * If seed >= 0, then that seed is used and the algorithm is deterministic.
 */
double randomNumber(int seedValue, double lowerLimit, double upperLimit)
{
//    std::random_device rd;
//    int RandomSeed = (seed < 0) ? rd() : seed;
//    std::mt19937 e2(RandomSeed);
//    std::uniform_real_distribution<> dist(lowerLimit,upperLimit);
//    return dist(e2);

    unsigned RandomSeed = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned Seed = (seedValue < 0) ? RandomSeed : seedValue;
    std::uniform_real_distribution<double> dist(lowerLimit,upperLimit);
    std::mt19937_64 rng(Seed);

    return dist(rng);
}


double round(double number, int decimalPlaces)
{
    if (decimalPlaces < 0) {
        std::cout << "Error: decimalPlaces argument in nmfUtils::round() function must be >= 0." << std::endl;
        decimalPlaces = 0;
    }

    double factor = std::pow(10,decimalPlaces);
    return  std::floor(number*factor+0.5)/factor;
}

void split(std::string main, std::string delim, std::string &str1, std::string &str2)
{
    std::string main2 = main;
    size_t sep = main2.find(delim);

    str1 = main2.erase(sep,main2.size());
    main2 = main;
    str2 = main2.erase(0,sep+1);
}

double CatchUnitsStringToValue(std::string val)
{
    double CatchUnitsVal = 0.0;

    if (val == "Hundreds of Fish")
        CatchUnitsVal =    0.1;
    else if (val == "Thousands of Fish")
        CatchUnitsVal =    1.0;
    else if (val == "Millions of Fish")
        CatchUnitsVal = 1000.0;

    return CatchUnitsVal;
} // end CatchUnitsStringToValue

double WeightUnitsStringToValue(std::string val)
{
    double WeightUnitsVal = 0.0;

    if (val == "Gram")
        WeightUnitsVal =    0.001;
    else if (val == "Kilograms")
        WeightUnitsVal =    1.0;
    else if (val == "Pounds")
        WeightUnitsVal = (1.0/2.2);

    return WeightUnitsVal;
} // end WeightUnitsStringToValue

double SizeUnitsStringToValue(std::string val)
{
    double SizeUnitsVal = 0.0;

    if (val == "Millimeters")
        SizeUnitsVal =    0.1;
    else if (val == "Centimeters")
        SizeUnitsVal =    1.0;
    else if (val == "Inches")
        SizeUnitsVal = 2.54;

    return SizeUnitsVal;
} // end SizeUnitsStringToValue


void readTableDescriptions(std::string TableName,
                          std::map<std::string,std::string> &TableDescription)
{
    std::string msg;
    std::string line;
    std::vector<std::string> parts;

    TableDescription.clear();

    std::ifstream fptr(TableName);
    if (fptr) {
        while (std::getline(fptr,line))
        {
            boost::algorithm::trim(line); // trims any spaces
            if (line[0] != '#') {
                boost::split(parts,line,boost::is_any_of("-"),boost::token_compress_on);
                if (parts.size() == 2) {
                    boost::algorithm::trim(parts[0]);
                    boost::algorithm::trim(parts[1]);
                    TableDescription[parts[0]] = parts[1];
                }
            }
        }
        fptr.close();
    } else {
        msg = "\nnmfUtils::readTableDescription Error: Couldn't open file: " + TableName;
        //QMessageBox::warning(0,tr("File Open Error"),tr(msg.c_str()),QMessageBox::Ok);
        std::cout << msg << std::endl;
    }
} // end readTableDescription


void readTableNames(std::map<std::string,std::vector<std::string> > *TableNames)
{
    int modelType;
    std::string file = nmfConstants::TableNamesFile;
    std::string line;
    std::string msg;
    std::vector<std::string> parts;
    std::ifstream fptr(file);
    std::vector<std::string> fields;

    for (auto i=0;i<nmfConstants::NumModelTypes; ++i) {
        TableNames[i].clear();
    }
    if (fptr) {
        while (std::getline(fptr,line))
        {
            boost::algorithm::trim(line); // trims any spaces
            if (line[0] != '#') {
                boost::split(parts,line,boost::is_any_of("\t "),boost::token_compress_on);
                if (parts.size() > 1) {
                    fields.clear();
                    for (int i=0; i<std::stoi(parts[2]); ++i) {
                        fields.push_back(parts[i+3]);
                    }
                    modelType = (parts[1] == "SSVPA") ? 0 : (parts[1] == "MSVPA") ? 1 : 2 ;
                    TableNames[modelType][parts[0]] = fields;
                } else {
                    std::cout << "nmfUtils::readTableNames Error in .MSVPA_X2/data/tableNames.dat." << std::endl;
                    break;
                }
            }
        }
        fptr.close();
    } else {
        msg = "\nnmfUtils::readTableNames Error: Couldn't open file: " + file;
        //QMessageBox::warning(0,tr("File Open Error"),tr(msg.c_str()),QMessageBox::Ok);
        std::cout << msg << std::endl;
    }
} // end readTableNames



bool errorCheck(nmfLogger *logger,
                std::string table,
                std::string field,
                std::map<std::string, std::vector<std::string> > &dataMap,
                std::string queryStr)
{
    if (dataMap[field].size() == 0) {
        logger->logMsg(nmfConstants::Error,"Error - Check " + table + " table. ");
        logger->logMsg(nmfConstants::Error,"Error - No data found for cmd: "+queryStr);
        return true; // there was an error
    }

    return false; // there was no error

} // end errorCheck


/*
 * Rescales matrix Xij by: log base 10 (X)
 */
void
rescaleMatrixLog(boost::numeric::ublas::matrix<double> &Matrix)
{
    int NumRows = Matrix.size1();
    int NumCols = Matrix.size2();

    // Rescale the matrix using the min and max values found for each species
    for (auto species=0; species<NumCols; ++species) {
        for (auto time=0; time<NumRows; ++time) {
            Matrix(time,species) = std::log10(Matrix(time,species));
        }
    }
}

/*
 * Rescales matrix Xij by: (X - Xmin) / (Xmax - Xmin)
 */
void
rescaleMatrixMinMax(boost::numeric::ublas::matrix<double> &Matrix)
{
    double den;
    double min;
    double max;
    int NumRows = Matrix.size1();
    int NumCols = Matrix.size2();
    std::vector<double> MinValues;
    std::vector<double> MaxValues;

    // Find min and max values for each species
    for (auto species=0; species<NumCols; ++species) {
        boost::numeric::ublas::matrix_column<boost::numeric::ublas::matrix<double> > aMatrixColumn(Matrix,species);
        auto result = std::minmax_element(aMatrixColumn.begin(), aMatrixColumn.end());
        MinValues.push_back(*result.first);
        MaxValues.push_back(*result.second);
    }

    // Rescale the matrix using the min and max values found for each species
    for (auto species=0; species<NumCols; ++species) {
        min = MinValues[species];
        max = MaxValues[species];
        den = (max - min);
        for (auto time=0; time<NumRows; ++time) {
            Matrix(time,species) = (Matrix(time,species) - min) / den;
        }
    }
}

std::string
to_string_scientificNotation(double val)
{
    std::ostringstream streamDouble; // Needed to stuff a double into a string with scientific notation

    streamDouble.str("");
    streamDouble << val;

    return streamDouble.str();
}

}
