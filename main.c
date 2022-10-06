#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Current program will display a table of 10 most active devices (which sent biggest amount of messages)

 static int devices(void *unused, int count, char **data, char **columns) {
    printf("\n");
    printf("\tppk: %s => ", data[0]);
    printf("messages: %s", data[1]);
	return 0;
}

int main(int argc, char *argv[]) {
	
    sqlite3 *db;
    char *err_msg = 0;
  
    
    // Open CASL DB
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open CASL Cloud database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    }
    
    
    // query to find 10 most active devices  
    char activeDevsQuery[256] = "SELECT device.number as ppk_number, COUNT(event.device_id) as messages" \
                                " FROM event LEFT JOIN device ON device.device_id = event.device_id" \
                                " GROUP BY event.device_id ORDER BY messages DESC LIMIT 10;"; 
								  
    printf("\n10 Most active devices: \n");
    
    rc = sqlite3_exec(db, activeDevsQuery, devices, 0, &err_msg);   
        
     
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
    
    sqlite3_close(db);  
    
    printf("\n\nQuery executed successfully! \n");
    
    system("pause");   
       
	return 0;
}
