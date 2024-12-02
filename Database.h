#include <sqlite3.h>
#include <iostream>
using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

class Database {
    private:
        sqlite3* db;
        char* errorMessage;
        int exitCode;

    public:
        Database(const string& dbName) {
            exitCode = sqlite3_open(dbName.c_str(), &db);
            if (exitCode) {
                cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
                db = nullptr;
            } else {
                cout << "Opened database successfully" << endl;
            }
        }

        ~Database() {
            if (db) {
                sqlite3_close(db);
                cout << "Closed database successfully" << endl;
            }
        }

        bool executeQuery(const string& query) {
            exitCode = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);
            if (exitCode != SQLITE_OK) {
                cerr << "SQL error: " << errorMessage << endl;
                sqlite3_free(errorMessage);
                return false;
            }
            return true;
        }

        sqlite3* getDb() const {
            return db;
        }
};

#endif