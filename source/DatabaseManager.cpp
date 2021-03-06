//////////////////////////////////////////////////////////////////////////
// Project - Offline
// All Game Code By Adam Hulbert
// For AIE Advanced Diploma - Artificial Intelligence for Games Term 2 2015
// 18/06/2015
/////////////////////////////////////////////////////////////////////////

#include "DatabaseManager.h"
#include "sqlite3.h"
#include <assert.h>
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

int DatabaseManager::s_Callback(void* dmInstance, int numArgs, char **data, char **columnName)
{	
	DatabaseManager* dm = reinterpret_cast<DatabaseManager*>(dmInstance);
    return dm->Callback(numArgs, data, columnName);
}

int DatabaseManager::Callback(int numArgs, char **data, char **columnName)
{	
	map<string, string> temp;
	for ( int i = 0; i < numArgs; ++i )
	{
		temp[string(columnName[i])] = data[i];
	}	
	databaseResponse.push_back(temp);
	return 0;
}

string DatabaseManager::GetValueString(unsigned int row, string col) 
{
	if ( databaseResponse.size() > row )
		return databaseResponse[row][col];
	return "";
}
int DatabaseManager::GetValueInt(int row, string col)
{
	string value = GetValueString(row, col);
	if ( value != "" )
		return std::atoi(value.c_str());
	return 0;
}
float DatabaseManager::GetValueFloat(int row, string col)
{
	string value = GetValueString(row, col);
	if ( value != "" ) 	
		return (float)atof(GetValueString(row, col).c_str());
	return 0.0f;
}

//Constructor/Destructor
DatabaseManager::DatabaseManager()
{
	sqlDataTypes[SQLITE_TYPE_NULL] = " NULL ";
	sqlDataTypes[SQLITE_TYPE_INTEGER] = " INTEGER ";
	sqlDataTypes[SQLITE_TYPE_REAL] = " REAL ";
	sqlDataTypes[SQLITE_TYPE_TEXT] = " TEXT ";
	sqlDataTypes[SQLITE_TYPE_BLOB] = " BLOB ";
}
DatabaseManager::~DatabaseManager(){}

	
//DatabaseManager::Insert
//table		- the table to insert to
//colNames  - comma seperated string the column names to insert to
//values	- comma seperated values to insert
//errorMsg	- pointer to errorMsg to fill on error
//returns true if no error
int DatabaseManager::Insert(string dbFile, string table, vector<string> colNames, vector<string> values, char* errorMsg)
{
	//reset the score info struct
	//info = EmptyScoreInfo; 
	databaseResponse.clear();

	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);
	string sql;
	if (colNames.size() > 0)
	{
		sql = "INSERT INTO " + table + "("; 
		for (int i = 0; i < colNames.size(); ++i)
		{
			sql += colNames[i];
			if (i != colNames.size() - 1)
				sql += ",";
		}
		sql += ") VALUES(";
		for (int i = 0; i < values.size(); ++i)
		{
			sql += values[i];
			if (i != values.size() - 1)
				sql += ",";
		}
		sql+= ");";
	}
	else
	{
		sql = "INSERT INTO " + table + " DEFAULT VALUES;";
	}
	

	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);
	int rowID = sqlite3_last_insert_rowid(db);
	sqlite3_close(db);
	if (errorMsg != NULL)
	{
		cout << "Database Insert Error, SQL :" << sql << endl;
		cout << "SQLite Error: " << errorMsg << endl;
	}
	return rowID;
}

	
//DatabaseManager::Select
//table		- the table to select from	
//columns	- columns to select
//sqlWhere	- where sql clause
//orderBy	- sort criteria
bool DatabaseManager::Select(string dbFile, string table, string columns, string sqlWhere, string orderBy, char* errorMsg, int limit) //values
{
	//reset the score info struct
	//info = EmptyScoreInfo; 
	databaseResponse.clear();

	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);

	//create the statement
	string sql = "SELECT " + columns + " FROM " + table;

	if ( sqlWhere.length() > 0 )
	{
		sql += " WHERE " + sqlWhere;
	}
	if ( orderBy.length() > 0 ) 
	{
		sql += " ORDER BY " + orderBy;
	}
	if (limit != 0 )
	{
		std::stringstream ss;
		ss << " LIMIT " << limit;
		sql += ss.str();
	}

	//run the query
	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);
	
	if  (errorMsg != NULL )
	{
		return false;
	}
	return true;
}

bool DatabaseManager::Create(string dbFile, string tableName, map<string, DB_SQLITE_DATATYPE> colNames, char* errorMsg)
{
	map<string, DB_SQLITE_DATATYPE>::iterator colIter;
	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);

	string sql = " CREATE TABLE " + tableName;
	sql += "(";

	for ( map<string, DB_SQLITE_DATATYPE>::iterator i = colNames.begin(); i != colNames.end(); ++i )
	{
		sql += " " + i->first + " ";
		sql += " " + sqlDataTypes[i->second] + ", ";
	}
	//remove the last comma and space for SQL syntax
	sql = sql.substr(0, sql.size()-2);
	sql += ");";

	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);
	
	if  (errorMsg != NULL )
	{
		return false;
	}
	return true;
}

int DatabaseManager::Rows()
{
	return databaseResponse.size();
}


////Example of use/////
///////////////////////

//char* error = NULL;
//DatabaseManager dm
//dm.Select("HighScores.db", "SCORES", "*", "", "", error);
//while(gamerunning)
//{
//	for (int i = 0; i < dm.Rows(); ++i )
//	{
//		std::cout << "Score: " << dm.GetValueString(i, "SCORE") << std::endl;
//		std::cout << "Name: " << dm.GetValueString(i, "NAME") << std::endl;
//	}
//}