#ifndef UTILS_H
#define UTILS_H

#include <QMessageBox>
#include <numeric>
#include <cmath>
#include <string>
#include <vector>

/**
 * @brief Shows a dialog with an error message.
 * @param msg Text to show in the dialog.
 */
void showErrorMessage(std::string msg);

/**
 * @brief Returns whether two numbers are within a certain tolerance from each other.
 *
 * For example, 1.0001 and 1.00015 would be considered approximately equal with a tolerance
 * of 0.0001
 */
bool approxEqual(double a, double b, double tolerance = 1e-5);

void printUsage();

std::vector<std::string> splitLine(std::string line, std::string delimiter=",");

std::string joinParts(std::vector<std::string> parts, std::string delimiter=",");

template <typename T>
double avgVec(std::vector<T> v)
{
    double sum = std::accumulate(v.begin(), v.end(), 0.);
    return sum / v.size();
}

#endif // UTILS_H
