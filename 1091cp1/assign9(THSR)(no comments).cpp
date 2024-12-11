#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 25
#define STAT 23
#define CAR 12
#define ROW 20
#define COL 5

#define DETAIL_INIT_200 DETAIL_INIT_100 DETAIL_INIT_100
#define DETAIL_INIT_100 DETAIL_INIT_50 DETAIL_INIT_50
#define DETAIL_INIT_50  DETAIL_INIT_10 DETAIL_INIT_10 DETAIL_INIT_10 DETAIL_INIT_10 DETAIL_INIT_10
#define DETAIL_INIT_10  DETAIL_INIT_2 DETAIL_INIT_2 DETAIL_INIT_2 DETAIL_INIT_2 DETAIL_INIT_2
#define DETAIL_INIT_2   DETAIL_INIT_1 DETAIL_INIT_1
#define DETAIL_INIT_1   {NULL, NULL, NULL, 0, NULL, NULL, 0},

int accessed_stations[STAT] = {};
int people = 0; // how many different people reserve
int fail = 0; // whether the reservation fails
int stat1 = -1, stat2 = -1; // decide the direction
int some_success_but_fail = 0;

struct detail{
	char name[NAME];
	int *start;
	int *dest;
	int tickets;
	int *car;
	int *seat;
	int size; // how many tickets can each person reserve?
};
typedef struct detail Detail;

struct table{
	int status;
	int who;
};
typedef struct table Table;
Table table[STAT][CAR][ROW*COL]; // [which station][which car][which seat(which row(1~20) and column(A~E))];

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

void seat_process(Detail *psg, int somebody, int origin_tickets, int ticket_order, int Car, int Seat){
	int Start = psg->start[origin_tickets + ticket_order];
	int Dest = psg->dest[origin_tickets + ticket_order];
			
		if(stat1 - stat2 < 0){ // N -> S
			for(int j = Start+1; j < Dest; ++j){
				if(table[j][Car-1][Seat].status == 2){
					printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
					fail = 1;
					return;
				}
			}
			if( ( Start-1 >= 0 && (table[Start][Car-1][Seat].status == 2 && table[Start-1][Car-1][Seat].status == 2) ) // not tail
			|| ( Dest+1 < STAT && (table[Dest][Car-1][Seat].status == 2 && table[Dest+1][Car-1][Seat].status == 2) )){ // not head
				printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
				fail = 1;
				return;
			}
			
			for(int j = Start+1; j < Dest; ++j){
				table[j][Car-1][Seat].status = 2; // all ordered seats are empty
				table[j][Car-1][Seat].who = somebody;
			}
			psg->car[origin_tickets + ticket_order] = Car;
			psg->seat[origin_tickets + ticket_order] = Seat;
			
			if(Start-1 >= 0 && Dest+1 < STAT){ // whether the stations are merged
				if(table[Start-1][Car-1][Seat].who == somebody && table[Start+1][Car-1][Seat].who == somebody){
					table[Start][Car-1][Seat].status = 2;
					table[Start][Car-1][Seat].who = somebody;
				}
				if(table[Dest-1][Car-1][Seat].who == somebody && table[Dest+1][Car-1][Seat].who == somebody){
					table[Dest][Car-1][Seat].status = 2;
					table[Dest][Car-1][Seat].who = somebody;
				}
			}
			
		}
		else if(stat1 - stat2 > 0){ // S -> N
			for(int j = Start-1; j > Dest; --j){
				if(table[j][Car-1][Seat].status == 2){
					printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
					fail = 1;
					return;
				}
			}
			if( ( Start+1 < STAT && (table[Start][Car-1][Seat].status == 2 && table[Start+1][Car-1][Seat].status == 2) ) // not head
			|| ( Dest-1 >= 0 && (table[Dest][Car-1][Seat].status == 2 && table[Dest-1][Car-1][Seat].status == 2) ) ){ // not tail
				printf("RESERVE FAILED.... (repeat seats)\n"); // the seat has been reserved already
				fail = 1;
				return;
			}
				
			for(int j = Start-1; j > Dest; --j){
				table[j][Car-1][Seat].status = 2; // all ordered seats are empty
				table[j][Car-1][Seat].who = somebody;
			}
			psg->car[ticket_order] = Car;
			psg->seat[ticket_order] = Seat;
				
			if(Dest-1 >= 0 && Start+1 < STAT){ // whether the stations are merged
				if(table[Dest-1][Car-1][Seat].who == somebody && table[Dest+1][Car-1][Seat].who == somebody){
					table[Dest][Car-1][Seat].status = 2;
					table[Dest][Car-1][Seat].who = somebody;
				}
				if(table[Start-1][Car-1][Seat].who == somebody && table[Start+1][Car-1][Seat].who == somebody){
					table[Start][Car-1][Seat].status = 2;
					table[Start][Car-1][Seat].who = somebody;
				}
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
	return Car;
}

int cal_seat(char queue[20][20], int order){
	int num = 0, Seat = 0;
	for(int i = 0; i < sizeof(queue[order]) / sizeof(queue[order][0]); ++i){
		if(queue[order][i] >= '0' && queue[order][i] <= '9') num = num*10 + (queue[order][i] - '0');
		else if(queue[order][i] >= 'A' && queue[order][i] <= 'E'){
			Seat = (num-1)*5 + queue[order][i]%5;
		}
	}
	return Seat;
}

void reserve(Detail *psg, int somebody, int origin_tickets, int ticket_order, char queue[20][20]){
	int Car = 0, Seat = 0;
	Car = cal_car(queue, 5+ticket_order*2);
	Seat = cal_seat(queue, 6+ticket_order*2);
	seat_process(psg, somebody, origin_tickets, ticket_order, Car, Seat);
	if(fail == 1) return;
}

void removeNtoS(int Start, int Dest, int Car, int Seat){
	for(int i = Start; i < Dest; ++i){
		if(accessed_stations[i] == 1) table[i][Car-1][Seat].status = 1;
		else table[i][Car-1][Seat].status = 0;
		table[i][Car-1][Seat].who = -1;
	}
}
void removeStoN(int Start, int Dest, int Car, int Seat){
	for(int i = Start; i > Dest; --i){
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
	
	if(table[Start][Car-1][Seat].status == 0 || table[Dest][Car-1][Seat].status == 0){
		printf("CANCELLATION FAILED.... (cannot find the stations information)\n");
		return;
	}
	
	if(stat1 - stat2 < 0){ // N -> S
		for(int i = Start+1; i < Dest; ++i){
			if(table[i][Car-1][Seat].status != 2){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n"); // reserved section doesn't include cancelled section
				return;
			}
		}
		
		for(int i = Start+1; i < Dest; ++i){
			if(table[i][Car-1][Seat].who != somebody){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				return;
			}
		}
	}
	else if(stat1 - stat2 > 0){ // S -> N
		for(int i = Start-1; i > Dest; --i){
			if(table[i][Car-1][Seat].status != 2){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n"); // reserved section doesn't include cancelled section
				return;
			}
		}
		
		for(int i = Start-1; i > Dest; --i){
			if(table[i][Car-1][Seat].who != somebody){
				printf("CANCELLATION FAILED.... (cannot find the seat information)\n");
				return;
			}
		}
	}
	
	remove_try(Start, Dest, Car, Seat);
	if(some_success_but_fail == 0) printf("CANCELLATION SUCCESSED!! %s %s (%s - %s)\n", queue[4], queue[5], queue[2], queue[3]);
}

void check(Detail *psg, int somebody, char queue[20][20]){
	int Car = 0, Seat = 0, num = 0;
	
	Car = cal_car(queue, 2);
	Seat = cal_seat(queue, 3);
	if((Car < 1 || Car > 12) || (Seat < 0 || Seat > 99)){
		printf("CHECK FAILED.... (cannot find the reservation data)\n");
		return;
	}
	
	int empty = 1; // doesn't reserve any ordered station
	int printed = 0;
	
	if(stat1 - stat2 < 0){ // N -> S
		for(int i = 0; i < STAT; ++i){
			if(table[i][Car-1][Seat].status == 2 && table[i][Car-1][Seat].who == somebody){
				empty = 0;
				if(printed == 0){
					printf("CHECK %s %s %s ->", queue[1], queue[2], queue[3]);
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
					printf("CHECK %s %s %s ->", queue[1], queue[2], queue[3]);
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
		int Start = psg->start[i];
		int Dest = psg->dest[i];
		remove_try(Start, Dest, psg->car[i], psg->seat[i]);
		psg->start[i] = -1;
		psg->dest[i] = -1;
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
	if( strcmp(queue[2], queue[3]) == 0 || // start == destination
		(table[Start][0][0].status != 1 || table[Dest][0][0].status != 1) || // either start or destination aren't accessed
		!( (Start - Dest > 0) && (stat1 - stat2 > 0) || ( (Start - Dest < 0) && (stat1 - stat2 < 0) ) ) ){  // not the same direction
		printf("RESERVE FAILED.... (station information has something wrong)\n");
		return;
	}
	
	int Tickets = 0;
	for(int i = 0; i < sizeof(queue[4]) / sizeof(queue[4][0]); ++i){
		if(queue[4][i] == 0) break;
		Tickets = Tickets * 10 + (queue[4][i] - '0');
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
			psg->start[psg->tickets] = station_search(queue[2]);
			psg->dest[psg->tickets] = station_search(queue[3]);
			reserve(psg, somebody, origin_tickets, i, queue);
			if(fail == 1){
				wrong_ticket = i;
				break;
			}
			++psg->tickets;
		}
		
	}
	if(fail == 1){
		clean(psg, wrong_ticket);
	}
	else{
		int Car = 0, Seat = 0, num = 0;
		for(int i = psg->tickets - Tickets; i < psg->tickets; ++i){
			printf("RESERVE SUCCESSED!! -> %s %s %s ", psg->name, queue[5 + (i - (psg->tickets - Tickets))*2], queue[6 + (i - (psg->tickets - Tickets))*2]);
			printf("(");
			num_to_station(psg->start[i]);
			printf(" - ");
			num_to_station(psg->dest[i]);
			printf(")\n");
		}
		if(somebody == people) ++people; // newly successfully reserved person +1
		if(psg->tickets+4 >= psg->size){
			int origin_tickets = psg->tickets;
            int origin_size = psg->size;
            psg->size *= 2;
			Detail temp = {NULL, NULL, NULL, origin_tickets, NULL, NULL, origin_size};
			temp.size = psg->size;
			temp.start = (int*)malloc(sizeof(int) * psg->size);
            temp.dest = (int*)malloc(sizeof(int) * psg->size);
            temp.car = (int*)malloc(sizeof(int) * psg->size);
            temp.seat = (int*)malloc(sizeof(int) * psg->size);
            for(int i = 0; i < psg->size; ++i){
                if(i < origin_size){
                	temp.start[i] = psg->start[i];
                	temp.dest[i] = psg->dest[i];
                	temp.car[i] = psg->car[i];
                	temp.seat[i] = psg->seat[i];
                }
                else{
                	temp.start[i] = -1;
                	temp.dest[i] = -1;
                    temp.car[i] = -1;
                    temp.seat[i] = -1;
                }
            }
            psg->start = temp.start;
            psg->dest = temp.dest;
            psg->car = temp.car;
            psg->seat = temp.seat;
		}
	}
}

int main(){
	Detail passengers[200] = {DETAIL_INIT_200};
	int stations, somebody;
	char station_seq[100] = {}, str[100] = {};
	for(int i = 0; i < 200; ++i){
		passengers[i].size = 20;
		passengers[i].start = (int*)malloc(sizeof(int) * passengers[i].size);
		passengers[i].dest = (int*)malloc(sizeof(int) * passengers[i].size);
		passengers[i].car = (int*)malloc(sizeof(int) * passengers[i].size);
		passengers[i].seat = (int*)malloc(sizeof(int) * passengers[i].size);
		for(int j = 0; j < passengers[i].size; ++j){
			passengers[i].start[j] = -1;
			passengers[i].dest[j] = -1;
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
	fgets(str, 100, stdin);
	scanf("%d", &stations);
	for(int i = 0; i < stations; ++i){
		scanf("%s", station_seq);
		for(int j = 0; j < strlen(station_seq); ++j){
			if(station_seq[j] == ',') station_seq[j] = '\0';
		}
		station_order(station_seq);
		if(stat1 == -1) stat1 = station_search(station_seq);
		else{
			if(stat2 == -1) stat2 = station_search(station_seq);
		}
	}
	getchar();
	fgets(str, 100, stdin);
	fgets(str, 100, stdin);
	fgets(str, 100, stdin);
	char request[100] = {};
	char end[50] = "===========(REQUEST END)===========\n";
	while(fgets(request, 100, stdin)){ // input request
		if(strlen(request) == 1 && request[0] == 10) break;
		for(int i = 0; i < 100; ++i){
			if(request[i] == '\n'){
				request[i] = '\0';
				break;
			}
		}
		char queue[20][20] = {}; // [the ith string][length of each string]
		int count = 0;
		char * pch = NULL;
		pch = strtok (request,", ");
		while (pch != NULL){
			strcpy(queue[count++], pch);
		    pch = strtok (NULL, ", ");
		}
		
		if(strcmp(queue[0], "RESERVE") == 0){
			somebody = people; // (default) first reserved
			for(int i = 0; i < people; ++i){
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
	for(int i = 0; i < 200; ++i){
		free(passengers[i].start);
		free(passengers[i].dest);
		free(passengers[i].car);
		free(passengers[i].seat);
	}
	return 0;
} 
