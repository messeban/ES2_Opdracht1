#include "PJ_RPI.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con)
{
 fprintf(stderr, "%s\n", mysql_error(con));
 mysql_close(con);
 exit(1);
}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

if (mysql_real_connect(con, "localhost", "webuser", "secretpassword",
 "globe_bank", 0, NULL, 0) == NULL)
 {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }
  if (mysql_query(con, "DROP TABLE IF EXISTS gpios")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "CREATE TABLE gpios (id INT(11) NOT NULL AUTO_INCREMENT, gpio VARCHAR(255),  IO TINYINT(1),   schakeltijdstip TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP, PRIMARY KEY (id) );")) {
      finish_with_error(con);
  }

	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}
	INP_GPIO(17);

    int buffer17 = (int)(GPIO_READ(17))>>17;
    int buffer18 = (int)(GPIO_READ(18))>>18;
    int buffer22 = (int)(GPIO_READ(22))>>22;

    char query[100];

    printf("GPIO 17 %d\n", (int)(GPIO_READ(17))>>17);
    printf("GPIO 18 %d\n", (int)(GPIO_READ(18))>>18);
    printf("GPIO 17 %d\n", (int)(GPIO_READ(22))>>22);
    
    sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('17',%d)",(int)(GPIO_READ(17))>>17);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('18',%d)",(int)(GPIO_READ(18))>>18);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('22',%d)",(int)(GPIO_READ(22))>>22);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    while(1){
	if((int)(GPIO_READ(17))>>17 != buffer17){
		printf("GPIO 17 %d\n", (int)(GPIO_READ(17))>>17);
        printf("GPIO 18 %d\n", (int)(GPIO_READ(18))>>18);
		printf("GPIO 22 %d\n", (int)(GPIO_READ(22))>>22);
        sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('17',%d)",(int)(GPIO_READ(17))>>17);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
	}

	if((int)(GPIO_READ(18))>>18 != buffer18){
        printf("GPIO 17 %d\n", (int)(GPIO_READ(17))>>17);
        printf("GPIO 18 %d\n", (int)(GPIO_READ(18))>>18);
		printf("GPIO 22 %d\n", (int)(GPIO_READ(22))>>22);
        sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('18',%d)",(int)(GPIO_READ(18))>>18);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
    }

    if((int)(GPIO_READ(22))>>22 != buffer22){
        printf("GPIO 17 %d\n", (int)(GPIO_READ(17))>>17);
        printf("GPIO 18 %d\n", (int)(GPIO_READ(18))>>18);
		printf("GPIO 22 %d\n", (int)(GPIO_READ(22))>>22);
        sprintf(query, "INSERT INTO gpios(gpio, IO) VALUES('22',%d)",(int)(GPIO_READ(22))>>22);
        if (mysql_query(con, query)) {
            finish_with_error(con);
        }
    }
    buffer17 = (int)(GPIO_READ(17))>>17;
    buffer18 = (int)(GPIO_READ(18))>>18;
    buffer22 = (int)(GPIO_READ(22))>>22;

    sleep(1);
    
    }

  mysql_close(con);
  exit(0);
  return 0;
  
  }
