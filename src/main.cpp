#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "square.h"

// in the real project there should be create appropriate constant 
enum MAGIC_CONSTANTS
{
    ARGUMENTS_COUNT = 6
};

void process_intersections(const std::string& input_path, const std::string& output_path) 
{
    std::ifstream infile(input_path);
    std::ofstream outfile(output_path, std::ios::out | std::ios::trunc);

    if (!infile.is_open()) 
    {
        std::cerr << input_path << std::endl;
        std::cerr << "Error: Unable to open input file." << std::endl;
        return;
    }

    if (!outfile.is_open()) 
    {
        std::cerr << output_path << std::endl;
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(infile, line)) 
    {
        std::stringstream ss(line);
        std::vector<int> values;
        std::string token;
        
        while (std::getline(ss, token, ',')) 
        {
            try 
            {
                values.push_back(std::stoi(token));
            } 
            catch (const std::invalid_argument&) 
            {
                outfile << "error" << std::endl;
                continue;
            }
        }
        
        if (values.size() != MAGIC_CONSTANTS::ARGUMENTS_COUNT) 
        {
            outfile << "error" << std::endl;
            continue;
        }
        
        int x1 = values[0], y1 = values[1], s1 = values[2];
        int x2 = values[3], y2 = values[4], s2 = values[5];
        
        try 
        {
            Square sq1(cv::Point(x1, y1), s1);
            Square sq2(cv::Point(x2, y2), s2);
            bool result = FigureOperations::intersect(sq1, sq2);
            outfile << x1 << "," << y1 << "," << s1 << ","
                    << x2 << "," << y2 << "," << s2 << ","
                    << (result ? "true" : "false") << std::endl;
        }
        catch (const std::exception&) 
        {
            outfile << x1 << "," << y1 << "," << s1 << ","
                    << x2 << "," << y2 << "," << s2 << ",error" << std::endl;
        }
    }
    
    infile.close();
    outfile.close();
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " /path/to/input.csv /path/to/output.csv" << std::endl;
        return 1;
    }
    
    process_intersections(argv[1], argv[2]);
    return 0;
}
