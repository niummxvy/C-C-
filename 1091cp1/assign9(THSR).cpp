#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 25
#define STAT 23
#define CAR 12
#define ROW 20
#define COL 5


int accessed_stations[STAT] = {};
int people = 0; // how many different people reserve
int fail = 0; // whether the reservation fails
int stat1 = -1, stat2 = -1; // decide the direction
int some_success_but_fail = 0;

struct detail{
	char name[NAME];
	char **start;
	char **dest;
	int tickets;
	int *car;
	int *seat;
	int size; // how many tickets can each person reserve?
};
typedef struct detail Detail;
Detail passengers[200];

struct table{
	int status;
	int who;
};
typedef struct table Table;
Table table[STAT][CAR][ROW*COL]; // [which station][which car][which seat(which row(1~20) and column(A~E))];
// table[STAT][CAR][ROW*COL].status == 0: not accessed; == 1: accessed but empty; == 2: accessed and reserved

int station_search(char station[20]){
	if(strcmp(station, "Nangang") == 0) return 0;
	else if(strcmp(station, "Taipei") == 0) return 2;
	else if(strcmp(station, "Banqiao") == 0) return 4;
	else if(strcmp(station, "Taoyuan") == 0) return 6;
	else if(strcmp(station, "Hsinchu") == 0) return 8;
	else if(strcmp(station, "Miaoli") == 0) return 10;
	else if(strcmp(station, "Taichung") == 0) return 12;
	else if(strcmp(station, "Changhua") == 0) return 14;
	else if(strcmp(station, "Yunlin") == 0) return 16;
	else if(strcmp(station, "Chiayi") == 0) return 18;
	else if(strcmp(station, "Tainan") == 0) return 20;
	else if(strcmp(station, "Zuoying") == 0) return 22;
}

void num_to_station(int num){
	if(num == 0) printf("Nangang");
	else if(num == 2) printf("Taipei");
	else if(num == 4) printf("Banqiao");
	else if(num == 6) printf("Taoyuan");
	else if(num == 8) printf("Hsinchu");
	else if(num == 10) printf("Miaoli");
	else if(num == 12) printf("Taichung");
	else if(num == 14) printf("Changhua");
	else if(num == 16) printf("Yunlin");
	else if(num == 18) printf("Chiayi");
	else if(num == 20) printf("Tainan");
	else if(num == 22) printf("Zuoying");
} 

void seat_process(Detail *psg, int somebody, int origin, int ticket_order, int Car, char Seat[4]){
	int num = 0;
//	printf("ticket order: %d\n", ticket_order);
	int Start = station_search(psg->start[origin + ticket_order]);
	int Dest = station_search(psg->dest[origin + ticket_order]);
	for(int i = 0; i < strlen(Seat); ++i){
		if(Seat[i] >= '0' && Seat[i] <= '9') num = num*10 + (Seat[i] - '0');
		else if(Seat[i] >= 'A' && Seat[i] <= 'E'){
			// A == 65, E == 69
			if(stat1 - stat2 < 0){ // N -> S
				for(int j = Start+1; j < Dest; ++j){
					if(table[j][Car-1][(num-1)*5 + Seat[i]%5].status == 2){
//						printf("table[%d][%d][%d]: %d\n", j, Car-1, (num-1)*5 + Seat[i]%5, table[j][Car-1][(num-1)*5 + Seat[i]%5]);
						printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
						fail = 1;
						return;
					}
				}
				if( ( Start-1 >= 0 && (table[Start][Car-1][(num-1)*5 + Seat[i]%5].status == 2 && table[Start-1][Car-1][(num-1)*5 + Seat[i]%5].status == 2) ) // not tail
				|| ( Dest+1 < STAT && (table[Dest][Car-1][(num-1)*5 + Seat[i]%5].status == 2 && table[Dest+1][Car-1][(num-1)*5 + Seat[i]%5].status == 2) )){ // not head
					printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
					fail = 1;
					return;
				}
				
			 	for(int j = Start+1; j < Dest; ++j){
					table[j][Car-1][(num-1)*5 + Seat[i]%5].status = 2; // all ordered seats are empty
					table[j][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
				}
//				printf("ticket_order: %d\n", ticket_order);
				psg->car[origin + ticket_order] = Car;
				psg->seat[origin + ticket_order] = (num-1)*5 + Seat[i]%5;
				
				// continuous stations
				if(Start-1 >= 0 && Dest+1 < STAT){ // whether the stations are merged
					if(table[Start-1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody && table[Start+1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody){
						table[Start][Car-1][(num-1)*5 + Seat[i]%5].status = 2;
						table[Start][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
					}
					if(table[Dest-1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody && table[Dest+1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody){
						table[Dest][Car-1][(num-1)*5 + Seat[i]%5].status = 2;
						table[Dest][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
					}
				}
				
			}
			else if(stat1 - stat2 > 0){ // S -> N
				for(int j = Start-1; j > Dest; --j){
					if(table[j][Car-1][(num-1)*5 + Seat[i]%5].status == 2){
//						printf("table[%d][%d][%d]: %d\n", j, Car-1, (num-1)*5 + Seat[i]%5, table[j][Car-1][(num-1)*5 + Seat[i]%5]);
						printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
						fail = 1;
						return;
					}
				}
				if( ( Start+1 < STAT && (table[Start][Car-1][(num-1)*5 + Seat[i]%5].status == 2 && table[Start+1][Car-1][(num-1)*5 + Seat[i]%5].status == 2) ) // not head
				|| ( Dest-1 >= 0 && (table[Dest][Car-1][(num-1)*5 + Seat[i]%5].status == 2 && table[Dest-1][Car-1][(num-1)*5 + Seat[i]%5].status == 2) ) ){ // not tail
					printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
					fail = 1;
					return;
				}
				
				for(int j = Start-1; j > Dest; --j){
					table[j][Car-1][(num-1)*5 + Seat[i]%5].status = 2; // all ordered seats are empty
					table[j][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
				}
				psg->car[ticket_order] = Car;
				psg->seat[ticket_order] = (num-1)*5 + Seat[i]%5;
					
				// continuous stations
				if(Dest-1 >= 0 && Start+1 < STAT){ // whether the stations are merged
					if(table[Dest-1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody && table[Dest+1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody){
						table[Dest][Car-1][(num-1)*5 + Seat[i]%5].status = 2;
						table[Dest][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
					}
					if(table[Start-1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody && table[Start+1][Car-1][(num-1)*5 + Seat[i]%5].who == somebody){
						table[Start][Car-1][(num-1)*5 + Seat[i]%5].status = 2;
						table[Start][Car-1][(num-1)*5 + Seat[i]%5].who = somebody;
					}
				}
			}
//			printf("No. %d, %s\n", somebody, psg.name);
//			printf("RESERVE SUCCESSED!! -> %s %d %s (%s - %s)\n", psg.name, Car, Seat, psg.start, psg.dest);
			break;
		}
	}
}

int station_order(char station[NAME]){ // open the permission of orderd station and determine direction
	accessed_stations[station_search(station)] = 1;
	for(int i = 0; i < CAR; ++i){
		for(int j = 0; j < ROW*COL; ++j){
			table[station_search(station)][i][j].status = 1;
		}
	}
}

int cal_car(char queue[20][20], int order){
	int Car = 0;
	for(int i = 0; i < sizeof(queue[order]) / sizeof(queue[order][0]); ++i){
		if(queue[order][i] == 0) break;
		Car = Car * 10 + (queue[order][i] - '0');
	}
//	if(queue[order][0] == '-') Car *= -1;
	return Car;
}

int cal_seat(char queue[20][20], int order){
	int num = 0, Seat = 0;
	for(int i = 0; i < sizeof(queue[order]) / sizeof(queue[order][0]); ++i){
		if(queue[order][i] >= '0' && queue[order][i] <= '9') num = num*10 + (queue[order][i] - '0');
		else if(queue[order][i] >= 'A' && queue[order][i] <= 'E'){
			// A == 65, E == 69
			Seat = (num-1)*5 + queue[order][i]%5;
		}
	}
//	if(queue[order][0] == '-') Seat *= -1;
	return Seat;
}

void reserve(Detail *psg, int somebody, int origin, int Ticket, char queue[20][20]){
	int Car = 0;
	Car = cal_car(queue, 5+Ticket*2);
	seat_process(psg, somebody, origin, Ticket, Car, queue[6+Ticket*2]);
	if(fail == 1) return;
}

void removeNtoS(int Start, int Dest, int Car, int Seat){
	for(int i = Start; i < Dest; ++i){
		// origin: table[i][Car][Seat].status == 2
		if(accessed_stations[i] == 1) table[i][Car-1][Seat].status = 1;
		else table[i][Car-1][Seat].status = 0;
		table[i][Car-1][Seat].who = -1;
	}
}
void removeStoN(int Start, int Dest, int Car, int Seat){
	for(int i = Start; i > Dest; --i){
		// origin: table[i][Car][Seat].status == 2
		if(accessed_stations[i] == 1) table[i][Car-1][Seat].status = 1;
		else table[i][Car-1][Seat].status = 0;
		table[i][Car-1][Seat].who = -1;
	}
}

void remove_try(int Start, int Dest, int Car, int Seat){
	if(stat1 - stat2 < 0){
		if((Start-2 >= 0 && Dest+2 < STAT) && (table[Start-2][Car-1][Seat].status == 2 && table[Dest+2][Car-1][Seat].status == 2)){ // remove middle, leave 2 sides
			removeNtoS(Start+1, Dest, Car, Seat);
		}
		else if((Start-2 >= 0 && Dest+2 < STAT) && (table[Start-2][Car-1][Seat].status != 2 && table[Dest+2][Car-1][Seat].status != 2)){ // remove all
			removeNtoS(Start, Dest+1, Car, Seat);
		}
		else if((Start-2 >= 0 && Dest+2 < STAT) && (table[Start-2][Car-1][Seat].status == 2 && table[Dest+2][Car-1][Seat].status != 2)){ // remove tail
			removeNtoS(Start+1, Dest+1, Car, Seat);
		}
		else if((Start-2 >= 0 && Dest+2 < STAT) && (table[Start-2][Car-1][Seat].status != 2 && table[Dest+2][Car-1][Seat].status == 2)){ // remove head
			removeNtoS(Start, Dest, Car, Seat);
		}
		else if(Start == 0 && Dest+2 < STAT){ // Start: Nangang
			if(table[Dest+2][Car-1][Seat].status == 2){ // remove head
				removeNtoS(Start, Dest, Car, Seat);
			}
			else if(table[Dest+2][Car-1][Seat].status != 2){ // remove all
				removeNtoS(Start, Dest+1, Car, Seat);
			}
		}
		else if(Start-2 >= 0 && Dest == STAT-1){ // Dest: Zuoying
			if(table[Start-2][Car-1][Seat].status == 2){ // remove tail
				removeNtoS(Start+1, Dest+1, Car, Seat);
			}
			else if(table[Start-2][Car-1][Seat].status != 2){ // remove all
				removeNtoS(Start, Dest+1, Car, Seat);
			}
		}
		else if(Start == 0 && Dest == STAT-1){ // remove all
			removeNtoS(Start, Dest+1, Car, Seat);
		}
	}
	else if(stat1 - stat2 > 0){
		if((Dest-2 >= 0 && Start+2 < STAT) && (table[Dest-2][Car-1][Seat].status == 2 && table[Start+2][Car-1][Seat].status == 2)){ // remove middle, leave 2 sides
			removeStoN(Start-1, Dest, Car, Seat);
		}
		else if((Dest-2 >= 0 && Start+2 < STAT) && (table[Dest-2][Car-1][Seat].status != 2 && table[Start+2][Car-1][Seat].status != 2)){ // remove all
			removeStoN(Start, Dest-1, Car, Seat);
		}
		else if((Dest-2 >= 0 && Start+2 < STAT) && (table[Dest-2][Car-1][Seat].status == 2 && table[Start+2][Car-1][Seat].status != 2)){ // remove tail
			removeStoN(Start, Dest, Car, Seat);
		}
		else if((Dest-2 >= 0 && Start+2 < STAT) && (table[Dest-2][Car-1][Seat].status != 2 && table[Start+2][Car-1][Seat].status == 2)){ // remove head
			removeStoN(Start-1, Dest-1, Car, Seat);
		}
		else if(Dest == 0 && Start+2 < STAT){ // Dest: Nangang
			if(table[Start+2][Car-1][Seat].status == 2){ // remove head
				removeStoN(Start-1, Dest-1, Car, Seat);
			}
			else if(table[Start+2][Car-1][Seat].status != 2){ // remove all
				removeStoN(Start, Dest-1, Car, Seat);
			}
		}
		else if(Dest-2 >= 0 && Start == STAT-1){ // Start: Zuoying
			if(table[Dest-2][Car-1][Seat].status == 2){ // remove tail
				removeStoN(Start, Dest, Car, Seat);
			}
			else if(table[Dest-2][Car-1][Seat].status != 2){ // remove all
				removeStoN(Start, Dest-1, Car, Seat);
			}
		}
		else if(Dest == 0 && Start == STAT-1){ // remove all
			removeStoN(Start, Dest-1, Car, Seat);
		}
	}
}

void cancel(Detail *psg, int somebody, char queue[20][20]){
	int Start = station_search(queue[2]);
	int Dest = station_search(queue[3]);
	int Car = 0, Seat = 0, num = 0;
	
	Car = cal_car(queue, 4);
	Seat = cal_seat(queue, 5);
	
	// Is the section accessed?
	if(table[Start][Car-1][Seat].status == 0 || table[Dest][Car-1][Seat].status == 0){
		printf("CANCELLATION FAILED.... (cannot find the stations information)\n");
		return;
	}
	
/*		if((Car < 1 || Car > 12) || (Seat < 0 || Seat > 99)){
		printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
		return;
	} */
	
	if(stat1 - stat2 < 0){ // N -> S
		// Does he/she really reserve this seat at ordered section?
		for(int i = Start+1; i < Dest; ++i){
			if(table[i][Car-1][Seat].status != 2){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n"); // reserved section doesn't include cancelled section
				return;
			}
		}
		
		// check whether the ordered seat is connected with the right person at each ordered station
		for(int i = Start+1; i < Dest; ++i){
//			printf("table[%d][%d][%d].who: %d\nsomebody: %d\n", i, Car-1, Seat, table[i][Car-1][Seat].who, somebody);
			if(table[i][Car-1][Seat].who != somebody){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				return;
			}
		}
	}
	else if(stat1 - stat2 > 0){ // S -> N
		// Does he/she really reserve this seat at ordered section?
		for(int i = Start-1; i > Dest; --i){
			if(table[i][Car-1][Seat].status != 2){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n"); // reserved section doesn't include cancelled section
				return;
			}
		}
		
		// check whether the ordered seat is connected with the right person at each ordered station
		for(int i = Start-1; i > Dest; --i){
//			printf("table[%d][%d][%d].who: %d\nsomebody: %d\n", i, Car-1, Seat, table[i][Car-1][Seat].who, somebody);
			if(table[i][Car-1][Seat].who != somebody){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				return;
			}
		}
	}
	
	
	// start cancelling
	// origin: table[i][Car][Seat].status == 2
	remove_try(Start, Dest, Car, Seat);
	if(some_success_but_fail == 0){
		printf("CANCELLATION SUCCESSED!! ");
		for(int i = 0; i < strlen(queue[4]); ++i) printf("%c", queue[4][i]);
		printf(" ");
		for(int i = 0; i < strlen(queue[5]); ++i) printf("%c", queue[5][i]);
		printf(" (%s - %s)\n", queue[2], queue[3]);
	}
}

void check(Detail *psg, int somebody, char queue[20][20]){
	int Car = 0, Seat = 0, num = 0;
	
	Car = cal_car(queue, 2);
	Seat = cal_seat(queue, 3);
/*	if((Car < 1 || Car > 12) || (Seat < 0 || Seat > 99)){
		printf("CHECK FAILED.... (cannot find the reservation data)\n");
		return;
	} */
	
	int empty = 1; // doesn't reserve any ordered station
	int printed = 0;
	
	if(stat1 - stat2 < 0){ // N -> S
		for(int i = 0; i < STAT; ++i){
			if(table[i][Car-1][Seat].status == 2 && table[i][Car-1][Seat].who == somebody){
				empty = 0;
				if(printed == 0){
					printf("CHECK %s ", queue[1], queue[2], queue[3]);
					for(int j = 0; j < strlen(queue[2]); ++j) printf("%c", queue[2][j]);
					printf(" ");
					for(int j = 0; j < strlen(queue[3]); ++j) printf("%c", queue[3][j]);
					printf(" ->");
					printed = 1;
				}
				for(int j = i; j < STAT; ++j){
					if(j == STAT-1 || (table[j+1][Car-1][Seat].status != 2 || table[j+1][Car-1][Seat].who != somebody)){ // j == STAT-1 == 22: terminal station: Zuoying
						printf(" (");
						if(i % 2 == 0) num_to_station(i);
						else num_to_station(i-1);
						printf(" - ");
						if(j % 2 == 0) num_to_station(j);
						else num_to_station(j+1);
						printf(")");
						i = j;
						break;
					}
				}
			}
		}
		
	}
	else if(stat1 - stat2 > 0){ // S -> N
		for(int i = STAT-1; i >= 0; --i){
			if(table[i][Car-1][Seat].status == 2 && table[i][Car-1][Seat].who == somebody){
				empty = 0;
				if(printed == 0){
					printf("CHECK %s ", queue[1], queue[2], queue[3]);
					for(int j = 0; j < strlen(queue[2]); ++j) printf("%c", queue[2][j]);
					printf(" ");
					for(int j = 0; j < strlen(queue[3]); ++j) printf("%c", queue[3][j]);
					printf(" ->");
					printed = 1;
				}
				for(int j = i; j >= 0; --j){
					if(j == 0 || (table[j-1][Car-1][Seat].status != 2 || table[j-1][Car-1][Seat].who != somebody)){ // j == 0: terminal station: Nangang
						printf(" (");
						if(i % 2 == 0) num_to_station(i);
						else num_to_station(i+1);
						printf(" - ");
						if(j % 2 == 0) num_to_station(j);
						else num_to_station(j-1);
						printf(")");
						i = j;
						break;
					}
				}
			}
		}
		
	}
	if(empty == 1) printf("CHECK FAILED.... (cannot find the reservation data)\n");
	else printf("\n");
}

void clean(Detail *psg, int Tickets){
	some_success_but_fail = 1;
	for(int i = psg->tickets - Tickets; i < psg->tickets; ++i){
		int Start = station_search(psg->start[i]);
		int Dest = station_search(psg->dest[i]);
		remove_try(Start, Dest, psg->car[i], psg->seat[i]);
		memset(psg->start[i], 0, NAME);
		memset(psg->dest[i], 0, NAME);
	}
	
	for(int j = psg->tickets - Tickets; j < psg->tickets; ++j){
		psg->car[j] = -1;
		psg->seat[j] = -1;
	}
	psg->tickets -= Tickets;
	if(psg->tickets == 0) memset(psg->name, 0, NAME);
	some_success_but_fail = 0;
}

void construct(Detail *psg, int somebody, char queue[20][20]){
	fail = 0;
	int wrong_ticket;
	int Start = station_search(queue[2]);
	int Dest = station_search(queue[3]);
//	printf("Start: %d, Dest: %d\n", Start, Dest);
	if( strcmp(queue[2], queue[3]) == 0 || // start == destination
		(table[Start][0][0].status != 1 || table[Dest][0][0].status != 1) || // either start or destination aren't accessed
		!( (Start - Dest > 0) && (stat1 - stat2 > 0) || ( (Start - Dest < 0) && (stat1 - stat2 < 0) ) ) ){  // not the same direction
		printf("RESERVE FAILED.... (station information has something wrong)\n");
		return;
	}
	
	int Tickets = 0;
	for(int i = 0; i < sizeof(queue[4]) / sizeof(queue[4][0]); ++i){
		if(queue[4][i] == 0) break;
		if(queue[4][i] >= '0' && queue[4][i] <= '9') Tickets = Tickets * 10 + (queue[4][i] - '0');
	}
	if(Tickets > 4){
		printf("RESERVE FAILED.... (too many seats)\n");
		return;
	}
	else{
		for(int i = 0; i < Tickets-1; ++i){
			for(int j = i+1; j < Tickets; ++j){
				if(strcmp(queue[5+i*2], queue[5+j*2]) == 0 && strcmp(queue[6+i*2], queue[6+j*2]) == 0){ // reserve same seats in one reservation
					printf("RESERVE FAILED.... (repeat seats)\n");
					return;
				}
			}
		}
		int origin_tickets = psg->tickets;
		strcpy(psg->name, queue[1]);
		for(int i = 0; i < Tickets; ++i){
			strcpy(psg->start[psg->tickets], queue[2]);
			strcpy(psg->dest[psg->tickets], queue[3]);
			reserve(psg, somebody, origin_tickets, i, queue);
			if(fail == 1){
				wrong_ticket = i;
				break;
			}
			++psg->tickets;
		}
		// not the first person: passengers[somebody].tickets += Tickets;
		// first person: passengers[somebody].tickets = Tickets;
		
	}
	if(fail == 1){
		// clean details
		clean(psg, wrong_ticket);
	}
	else{
		int Car = 0, Seat = 0, num = 0;
		for(int i = psg->tickets - Tickets; i < psg->tickets; ++i){
			printf("RESERVE SUCCESSED!! -> %s ", psg->name);
			for(int j = 0; j < strlen(queue[5 + (i - (psg->tickets - Tickets))*2]); ++j) printf("%c", queue[5 + (i - (psg->tickets - Tickets))*2][j]);
			printf(" ");
			for(int j = 0; j < strlen(queue[6 + (i - (psg->tickets - Tickets))*2]); ++j) printf("%c", queue[6 + (i - (psg->tickets - Tickets))*2][j]);
			printf(" (%s - %s)\n", psg->start[i], psg->dest[i]);
		}
		if(somebody == people) ++people; // newly successfully reserved person +1
		if(psg->tickets+4 >= psg->size){
			int origin_tickets = psg->tickets;
            int origin_size = psg->size;
            psg->size *= 2;
            Detail *temp = NULL;
            temp = (Detail*)malloc(sizeof(Detail));
            temp->start = (char**)malloc(sizeof(char*) * psg->size);
            temp->dest = (char**)malloc(sizeof(char*) * psg->size);
            for(int i = 0; i < psg->size; ++i){
                temp->start[i] = (char*)calloc('0', sizeof(char) * NAME);
                temp->dest[i] = (char*)calloc('0', sizeof(char) * NAME);
            }
//          printf("psg->start(before copy)------------(1)\n");
//          for(int i = 0; i < psg->tickets; ++i) printf("[%d]: %s\n", i, psg->start[i]);
            for(int i = 0; i < psg->tickets; ++i){
                for(int j = 0; j < strlen(psg->start[i]); ++j){
                    temp->start[i][j] = psg->start[i][j];
                }
                for(int j = 0; j < strlen(psg->dest[i]); ++j){
                    temp->dest[i][j] = psg->dest[i][j];
                }
            }
            for(int i = 0; i < origin_size; ++i){
                free(psg->start[i]);
                free(psg->dest[i]);
            }
            psg->start = temp->start;
            psg->dest = temp->dest;
//          free(temp->start);
//          free(temp->dest);
//          printf("psg->start(temp is freed)------------(4)\n");
//          for(int i = 0; i < psg->size; ++i) printf("[%d]: %s\n", i, psg->start[i]);

            temp->car = (int*)malloc(sizeof(int) * psg->size);
            temp->seat = (int*)malloc(sizeof(int) * psg->size);
            for(int i = 0; i < psg->size; ++i){
                if(i < origin_size){
                	temp->car[i] = psg->car[i];
                	temp->seat[i] = psg->seat[i];
                }
                else{
                    temp->car[i] = -1;
                    temp->seat[i] = -1;
                }
            }
            psg->car = temp->car;
//          for(int i = 0; i < psg->size; ++i) printf("[%d]: %d\n", i, psg->car[i]);
            psg->seat = temp->seat;
//          free(temp);
		}
	}
}

int main(){
	int stations, somebody;
	char station_seq[100] = {}, str[100] = {};
	for(int i = 0; i < 200; ++i){
		passengers[i].size = 300;
		passengers[i].start = (char**)malloc(sizeof(char*) * passengers[i].size);
		passengers[i].dest = (char**)malloc(sizeof(char*) * passengers[i].size);
		for(int j = 0; j < passengers[i].size; ++j){
			passengers[i].start[j] = (char*)malloc(sizeof(char) * NAME);
			passengers[i].dest[j] = (char*)malloc(sizeof(char) * NAME);
		}
		passengers[i].car = (int*)malloc(sizeof(int) * passengers[i].size);
		passengers[i].seat = (int*)malloc(sizeof(int) * passengers[i].size);
		for(int j = 0; j < passengers[i].size; ++j){
			passengers[i].car[j] = -1;
			passengers[i].seat[j] = -1;
		}
	}
	for(int i = 0; i < STAT; ++i){
		for(int j = 0; j < CAR; ++j){
			for(int k = 0; k < ROW*COL; ++k){
				table[i][j][k].status = 0;
				table[i][j][k].who = -1;
			}
		}
	}
//	gets("=====(TRAIN INFORMATION BEGIN)=====\n");
	fgets(str, 100, stdin);
	scanf("%d", &stations);
	for(int i = 0; i < stations; ++i){
		scanf("%s", station_seq);
		for(int j = 0; j < strlen(station_seq); ++j){
			if(station_seq[j] == ',') station_seq[j] = '\0';
		}
//		printf("%s\n", station_seq);
		station_order(station_seq);
		if(stat1 == -1) stat1 = station_search(station_seq);
		else{
			if(stat2 == -1) stat2 = station_search(station_seq);
		}
	}
	getchar();
//	gets("======(TRAIN INFORMATION END)======\n");
//	gets("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
//	gets("========(REQUEST BEGIN)==========\n");
	fgets(str, 100, stdin);
	fgets(str, 100, stdin);
	fgets(str, 100, stdin);
	// at most 4 tickets per person
	char request[100] = {};
	char end[50] = "===========(REQUEST END)===========\n";
	while(fgets(request, 100, stdin)){ // input request
//		getchar();
//		for(int i = 0; i < strlen(request); ++i) printf("%d ", request[i]);
//		printf("\n");
//		for(int i = 0; i < strlen(end); ++i) printf("%d ", end[i]);
//		printf("\n");
		if(strlen(request) == 1 && request[0] == 10) break;
//		printf("request: %s\n", request);
		for(int i = 0; i < 100; ++i){
			if(request[i] == '\n'){
				request[i] = 0;
				break;
			}
		}
		char queue[20][20] = {}; // [the ith string][length of each string]
		int count = 0;
//		fail = 0;
		char * pch = NULL;
		// split request
		pch = strtok (request,", ");
		while (pch != NULL){
//			printf ("%s\n",pch);
			strcpy(queue[count++], pch);
		    pch = strtok (NULL, ", ");
		}
		
		// do what the commands request to do
		if(strcmp(queue[0], "RESERVE") == 0){
			// constructor
			somebody = people; // (default) first reserved
			// check whether the person reserve again
			for(int i = 0; i < people; ++i){
//				printf("%s, %s\n", passengers[i].name, queue[1]);
				if(strcmp(passengers[i].name, queue[1]) == 0){
					somebody = i;
					break;
				}
			}
			construct(&passengers[somebody], somebody, queue);
		}
		else if(strcmp(queue[0], "CANCEL") == 0){
			somebody = -1;
			for(int i = 0; i < people; ++i){
				if(strcmp(passengers[i].name, queue[1]) == 0){
					somebody = i;
					break;
				}
			}
			if(somebody == -1){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				continue;
			}
			cancel(&passengers[somebody], somebody, queue);
		}
		else if(strcmp(queue[0], "CHECK") == 0){
			int exist = 0; // Does the person reserved any seat?
			somebody = people; // (default) first reserved
			for(int i = 0; i < people; ++i){
				if(strcmp(passengers[i].name, queue[1]) == 0){
					somebody = i;
					exist = 1;
					break;
				}
			}
			if(exist == 0) printf("CHECK FAILED.... (cannot find the reservation data)\n");
			else check(&passengers[somebody], somebody, queue);
		}
		if(strcmp(request, end) == 0) break; 
	}
//	gets("========(REQUEST END)==========\n");
	// free
	for(int i = 0; i < 200; ++i){
		for(int j = 0; j < passengers[i].size; ++j){
			free(passengers[i].start[j]);
			free(passengers[i].dest[j]);
		}
		free(passengers[i].start);
		free(passengers[i].dest);
		free(passengers[i].car);
		free(passengers[i].seat);
	}
	return 0;
} 

/*
=====(TRAIN INFORMATION BEGIN)=====



======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========



===========(REQUEST END)===========
*/

/* N -> S
=====(TRAIN INFORMATION BEGIN)=====
5
Taipei, Hsinchu, Taichung, Tainan, Zuoying
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
*/

/* N -> S (terminal)
=====(TRAIN INFORMATION BEGIN)=====
6
Nangang, Taipei, Hsinchu, Taichung, Tainan, Zuoying
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
*/

/* S -> N (terminal)
=====(TRAIN INFORMATION BEGIN)=====
7
Zuoying, Tainan, Yunlin, Taichung, Hsinchu, Taipei, Nangang
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
*/

/* stop at all stations (N -> S)
=====(TRAIN INFORMATION BEGIN)=====
12
Nangang, Taipei, Banqiao, Taoyuan, Hsinchu, Miaoli, Taichung, Changhua, Yunlin, Chiayi, Tainan, Zuoying
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
*/

/*
RESERVE Chi-Hung, Nangang, Zuoying, 1, 1 1A
CANCEL Chi-Hung, Taipei, Tainan, 1 1A
CHECK Chi-Hung, 1 1A
RESERVE Angel, Banqiao, Chiayi, 1, 1 1A
CANCEL Angel, Taoyuan, Yunlin, 1 1A
CHECK Chi-Hung, 1 1A
CHECK Angel, 1 1A
RESERVE Chi-Hung, Hsinchu, Changhua, 1, 1 1A
CANCEL Chi-Hung, Miaoli, Taichung, 1 1A
CHECK Chi-Hung, 1 1A
CHECK Angel, 1 1A
CHECK Chi-Hung, -1 1A
===========(REQUEST END)===========
*/

/*
RESERVE Angel, Taipei, Chiayi, 10, 2 1D, 2 1E, 2 2D, 2 2E, 3 1D, 3 1E, 3 2D, 3 2E, 4 1D, 4 1E
RESERVE Angel, Taipei, Taichung, 10, 2 1D, 2 1E, 2 2D, 2 2E, 3 1D, 3 1E, 3 2D, 3 2E, 4 1D, 4 1E
RESERVE Angel, Taipei, Taichung, 4, 3 1E, 2 2D, 3 2E, 4 1D
RESERVE Angel, Taipei, Taichung, 1, 2 2D
RESERVE Angel, Hsinchu, Tainan, 4, 4 1E, 2 2D, 3 2E, 4 1D
CHECK Angel 3 1E
CHECK Angel 3 2E
CHECK Angel 4 1E
CHECK Angel 2 2D
CANCEL Angel, Taichung, Hsinchu, 4 1E
CHECK Angel 4 1E
===========(REQUEST END)===========
*/

/* same seat, reserved by different people, and cancelled by the latter person who reserved the same seat
RESERVE Chi-Hung, Taipei, Taichung, 1, 6 3A
RESERVE Angel, Taipei, Taichung, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CANCEL Angel, Taipei, Taichung, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CANCEL Chi-Hung, Taipei, Taichung, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Noname 6 3A
===========(REQUEST END)===========

RESERVE Chi-Hung, Taichung, Taipei, 1, 6 3A
RESERVE Angel, Taichung, Taipei, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CANCEL Angel, Taichung, Taipei, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CANCEL Chi-Hung, Taichung, Taipei, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Noname 6 3A
===========(REQUEST END)===========
*/

/* not continuous same seat in one reservation
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 6 3A, 6 3B, 6 3C, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Chi-Hung, 6 3B
CHECK Chi-Hung, 6 3C
RESERVE Chi-Hung, Taipei, Hsinchu, 3, 6 3A, 6 3B, 6 3C
===========(REQUEST END)===========

RESERVE Chi-Hung, Hsinchu, Taipei, 4, 6 3A, 6 3B, 6 3C, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Chi-Hung, 6 3B
CHECK Chi-Hung, 6 3C
RESERVE Chi-Hung, Hsinchu, Taipei, 3, 6 3A, 6 3B, 6 3C
===========(REQUEST END)===========
*/

/* S -> N
RESERVE Chi-Hung, Hsinchu, Taipei, 3, 6 3A, 6 3B, 6 3C
CHECK Chi-Hung, 6 3A
===========(REQUEST END)===========
*/

/* first is successful, second is failed, should I print the successful info from first ticket? NO
RESERVE Chi-Hung, Taipei, Taichung, 1, 6 3A
RESERVE Angel, Hsinchu, Tainan, 2, 6 3E, 6 3A
CHECK Angel, 6 3E
RESERVE Angel, Taichung, Tainan, 1, 6 3E
CHECK Chi-Hung, 6 3A
===========(REQUEST END)===========

RESERVE Chi-Hung, Taichung, Taipei, 1, 6 3A
RESERVE Angel, Tainan, Hsinchu, 2, 6 3E, 6 3A
CHECK Angel, 6 3E
RESERVE Angel, Tainan, Taichung, 1, 6 3E
CHECK Chi-Hung, 6 3A
===========(REQUEST END)===========
*/

/* continuous stations but different people
RESERVE Chi-Hung, Taipei, Taichung, 1, 6 3A
RESERVE Angel, Taichung, Zuoying, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
RESERVE Angel, Taichung, Zuoying, 1, 6 3B
RESERVE Chi-Hung, Taipei, Taichung, 1, 6 3B
CHECK Angel, 6 3B
CHECK Chi-Hung, 6 3B
===========(REQUEST END)===========

RESERVE Chi-Hung, Taichung, Taipei, 1, 6 3A
RESERVE Angel, Zuoying, Taichung, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
RESERVE Angel, Zuoying, Taichung, 1, 6 3B
RESERVE Chi-Hung, Taichung, Taipei, 1, 6 3B
CHECK Angel, 6 3B
CHECK Chi-Hung, 6 3B
===========(REQUEST END)===========
*/

/* only take 2 stations per ticket
RESERVE Chi-Hung, Nangang, Taipei, 1, 6 3A
RESERVE Roger, Banqiao, Taoyuan, 1, 6 3A
RESERVE Angel, Taipei, Banqiao, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Roger, 6 3A
CANCEL Angel, Taipei, Banqiao, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Roger, 6 3A
===========(REQUEST END)===========


=====(TRAIN INFORMATION BEGIN)=====
4
Taoyuan, Banqiao, Taipei, Nangang
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
RESERVE Chi-Hung, Taipei, Nangang, 1, 6 3A
RESERVE Roger, Taoyuan, Banqiao, 1, 6 3A
RESERVE Angel, Banqiao, Taipei, 1, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Roger, 6 3A
CANCEL Angel, Banqiao, Taipei, 6 3A
CHECK Chi-Hung, 6 3A
CHECK Angel, 6 3A
CHECK Roger, 6 3A
===========(REQUEST END)===========
*/

/*
=====(TRAIN INFORMATION BEGIN)=====
12
Zuoying, Tainan, Chiayi, Yunlin, Changhua, Taichung, Miaoli, Hsinchu, Taoyuan, Banqiao, Taipei, Nangang
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
*/

/* cancel many sections
RESERVE Chi-Hung, Nangang, Zuoying, 1, 6 3A
CANCEL Chi-Hung, Taipei, Banqiao, 6 3A
CANCEL Chi-Hung, Hsinchu, Taichung, 6 3A
CANCEL Chi-Hung, Changhua, Yunlin, 6 3B
CANCEL Chi-Hung, Tainan, Zuoying, 6 3A
CHECK Chi-Hung, 6 3A
===========(REQUEST END)===========

RESERVE Chi-Hung, Zuoying, Nangang, 1, 6 3A
CANCEL Chi-Hung, Banqiao, Taipei, 6 3A
CANCEL Chi-Hung, Taichung, Hsinchu, 6 3A
CANCEL Chi-Hung, Yunlin, Changhua, 6 3B
CANCEL Chi-Hung, Zuoying, Tainan, 6 3A
CHECK Chi-Hung, 6 3A
===========(REQUEST END)===========
*/

/* reserve again(same people)
RESERVE Chi-Hung, Taipei, Hsinchu, 3, 6 3A, 6 3B, 6 3C
RESERVE Angel, Taipei, Taichung, 4, 2 1D, 2 1E, 2 2D, 2 2E
RESERVE Roger, Taipei, Hsinchu, 3, 7 3A, 7 3B, 7 3C
RESERVE Chi-Hung, Taipei, Hsinchu, 3, 7 3E, 7 3C, 7 3D
RESERVE Angel, Taichung, Tainan, 4, 2 1D, 2 1E, 6 3B, 6 3C
RESERVE Roger, Hsinchu, Changhua, 1, 2 2E
RESERVE Roger, Hsinchu, Changhua, 1, 6 3B
RESERVE Roger, Hsinchu, Miaoli, 1, 6 3C
CHECK Chi-Hung, 6 3A
CHECK Chi-Hung, 6 3B
CHECK Chi-Hung, 6 3C
CHECK Angel, 6 3A
CHECK Angel, 6 3B
CHECK Angel, 6 3C
CHECK Angel, 2 1D
CHECK Angel, 2 1E
CHECK Angel, 2 2D
CHECK Angel, 2 2E
CHECK Roger, 2 2E
CHECK Roger, 6 3B
CHECK Roger, 6 3C
===========(REQUEST END)===========


RESERVE Chi-Hung, Hsinchu, Taipei, 3, 6 3A, 6 3B, 6 3C
RESERVE Angel, Taichung, Taipei, 4, 2 1D, 2 1E, 2 2D, 2 2E
RESERVE Roger, Hsinchu, Taipei, 3, 7 3A, 7 3B, 7 3C
RESERVE Chi-Hung, Hsinchu, Taipei, 3, 7 3E, 7 3C, 7 3D
RESERVE Angel, Tainan, Taichung, 4, 2 1D, 2 1E, 6 3B, 6 3C
RESERVE Roger, Changhua, Hsinchu, 1, 2 2E
RESERVE Roger, Changhua, Hsinchu, 1, 6 3B
RESERVE Roger, Miaoli, Hsinchu, 1, 6 3C
CHECK Chi-Hung, 6 3A
CHECK Chi-Hung, 6 3B
CHECK Chi-Hung, 6 3C
CHECK Angel, 6 3A
CHECK Angel, 6 3B
CHECK Angel, 6 3C
CHECK Angel, 2 1D
CHECK Angel, 2 1E
CHECK Angel, 2 2D
CHECK Angel, 2 2E
CHECK Roger, 2 2E
CHECK Roger, 6 3B
CHECK Roger, 6 3C
===========(REQUEST END)===========
*/

/*
=====(TRAIN INFORMATION BEGIN)=====
5
Taipei, Hsinchu, Taichung, Tainan, Zuoying
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 1 3A, 1 3B, 1 3C, 1 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 2 3A, 2 3B, 2 3C, 2 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 3 3A, 3 3B, 3 3C, 3 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 4 3A, 4 3B, 4 3C, 4 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 5 3A, 5 3B, 5 3C, 5 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 6 3A, 6 3B, 6 3C, 6 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 7 3A, 7 3B, 7 3C, 7 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 8 3A, 8 3B, 8 3C, 8 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 9 3A, 9 3B, 9 3C, 9 3D
RESERVE Chi-Hung, Taipei, Hsinchu, 4, 10 3A, 10 3B, 10 3C, 10 3D
===========(REQUEST END)===========
*/

/*
RESERVE Chi-Hung, Taipei, Hsinchu, 1, 6 3A
RESERVE Chi-Hung, Taichung, Tainan, 1, 6 3A
CANCEL Chi-Hung, Hsinchu, Taichung, 6 3A
===========(REQUEST END)===========
*/

/*
=====(TRAIN INFORMATION BEGIN)=====
12
Nangang, Taipei, Banqiao, Taoyuan, Hsinchu, Miaoli, Taichung, Changhua, Yunlin, Chiayi, Tainan, Zuoying
======(TRAIN INFORMATION END)======
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
==========(REQUEST BEGIN)==========
RESERVE Chi-Hung, Taipei, Hsinchu, 3, 6 3A, 6 3B, 6 3C
RESERVE Chih-Ling, Hsinchu, Miaoli, 1, 6 3A
RESERVE Chi-Hung, Miaoli, Yunlin, 3, 6 3A, 6 3B, 6 3C
CHECK Chi-Hung, 6 3A
RESERVE Angel, Taipei, Taichung, 4, 3 1D, 3 1E, 2 2D, 2 2E
CHECK Sam, 2 2A
RESERVE Joy, Nangang, Zuoying, 1, 6 3B
CHECK Chi-Hung, 6 3A
RESERVE Roger, Taipei, Zuoying, 2, 1 1A, 1 1E
CANCEL Chi-Hung, Taipei, Yunlin, 6 3C
RESERVE Allen, Taipei, Miaoli, 2, 10 17B, 10 17C
RESERVE Samuel, Taichung, Taichung, 1, 6 3A
RESERVE Ting-Shan, Hsinchu, Taichung, 1, 10 3A
CANCEL Joy, Nangang, Chiayi, 6 3B
RESERVE Chi-Hung, Tainan, Zuoying, 1, 6 3A
CANCEL Angel, Taipei, Hsinchu, 6 3B
RESERVE Sam, Yunlin, Nangang, 4, 2 1A, 2 1B, 2 2A, 2 2B
RESERVE Grace, Yunlin, Hsinchu, 2, 2 2A, 2 3A
CANCEL Chi-Hung, Taipei, Taichung, 6 3C
RESERVE Ting-Shan, Taichung, Yunlin, 1, 10 3A
CANCEL Angel, Taichung, Hsinchu, 2 1E
CHECK Sam, 2 1A
CHECK Yen-Chi, 6 3A
CANCEL Angel, Taipei, Taichung, 2 1E
CHECK Ting-Shan, 10 3A
CANCEL Chi-Hung, Taipei, Miaoli, 6 3B
CHECK Chi-Hung, 6 3B
RESERVE Starbucks, Banqiao, Hsinchu, 2, 12 20D, 12 20E
RESERVE Louis, Taichung, Zuoying, 5, 1 1A, 1 1B, 1 1C, 1 1D, 1 1E
CHECK Angel, 2 1D
===========(REQUEST END)===========
*/

