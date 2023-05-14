/**
 * @cond DOXYGEN SKIPS THIS
 * Contributor(s): Andrew Brevick, Cuong Ha
 * File name: election.h
 * Description: Parent class to be inherited by specific election strategies
 * @endcond
 */

#ifndef ELECTION_H
#define ELECTION_H

#include<string>
#include<iostream>
#include<fstream>
#include<vector>

class Election {
    public:
        /**
        * @brief Virtual destructor to destroy derived classes when base class is destroyed
        */
        virtual ~Election();

        /**
        * @brief Virtual function that is going to be overloaded in  IR and CPL
        */
        virtual void ProcessElection(std::string &results_top, std::string &results_table) {}

        /**
         * @brief Set the File Path for input and audit
         * @param input_name filename and extension for input ballot file
         * @param audit_file filename and extension for audit file
         */
        void SetFilePaths(std::string in_nm, std::string aud_nm);

        /**
        * @brief Function used to perform a fair coin toss to break tied results
        * @param count Number of entities to be chosen from
        * @return A random index within [0, count)
        */
        int FlipCoin(int count);

        /**
        * @brief Function used to intialize an empty audit file
        * @return 0 if succeeded, -1 if failed for any reason
        */
        int CreateAuditFile();

        /**
        * @brief Functioned used to write into the audit file that has been created previously
        * @param write_data
        * @return 0 if succeeded, -1 if failed for any reason
        */
        int WriteAuditFile(std::string write_data);

        /**
         * @brief input file stream object
         * 
         */
        std::ifstream input_file;

    protected:
        /**
         * @brief name and extension of audit file
         * 
         */
        std::string audit_name;
        /**
         * @brief name and extension of input file
         * 
         */
        std::string input_name;
        /**
         * @brief audit file stream object
         * 
         */
        std::ofstream audit_file; 

};

#endif