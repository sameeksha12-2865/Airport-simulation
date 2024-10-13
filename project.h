//		project.h

#define NAME_LEN	30
#define	MAX_FLIGHTS	25	// Max number of flights an airport can accommodate
#define MAX_RUNWAYS	10	// Max number of runways
#define	MAX_PASSENGERS	300	// Max number of passengers inside the airport
#define	MAX_C_BAGS	3	// Max number of checkin baggages
#define	MAX_WEIGHT	40.0	// Max weight of checkin baggages
#define BOARD_LEN	15	// 
#define AIRWAYS_LEN	30	// Air India, Lufthansa, etc
#define F_LEN		20
#define CITY_LEN	20  	// Length of source or destination city
#define SEAT_LEN	5	// For holding seat number (A1, A10, B1, etc)
#define TIME_LEN	6	// Flight Boarding time
#define DATE_LEN	20	// dd:mm:yyyy
#define DET_LEN		10	// 1 of 3, 2 of 3, etc
#define ID_LEN		10	// Length of ID (Alphanumeric) 
#define NUM_ENTRIES	10 	// Number of entries into the airport
#define STAFF_ENTRY	1	// The entry point for the staff
#define OTHER_ENTRY	2	// Entry point for the others
#define HOUSE_ENTRY	3	// Entry for housekeeping people
#define PASS_ENTRY_MIN	4	// Entry gate number for passengers lies between 4
				// and 9
#define PASS_ENTRY_MAX  9	
#define MAX_STAFF	100	// Max number of staff numbers who can be inside the
				// airport
#define MAX_HOUSE	100	// Max number of housekeeping people who can be 
				// inside the airport
#define MAX_OTHERS	100	// Max num of others (security, vendors, etc)
#define MAX_PIECES	600	// Max number of checked-in luggage pieces (all 
				// passengera put together)

#define STATUS_LEN	20

typedef struct c_luggage_tag
{
	char name [NAME_LEN];
	char Airways [AIRWAYS_LEN];	// Air India, National Airways, etc
	char flightNumber [F_LEN];
	char details [DET_LEN];		// Number of bags 1 of 3, 2 of 3, etc
	int boardId;			// Boarding number ID
	float weight;			// Total weight 
} C_LUGGAGE_TAG;

typedef struct conveyorbelt
{
	int beltNum;		// Conveyor belt number
	C_LUGGAGE_TAG eachbag;	// Identity of each piece
	struct conveyorbelt *next;
} CONVEYORBELT;

typedef struct flight
{
	char Airways [AIRWAYS_LEN];	// Air India, National Airways, etc
	char flightNumber [F_LEN];	// Example NA4321
	char source [CITY_LEN];		// Source city
	char destination [CITY_LEN];	// Destination city
	char ArrDepart;			// A - Arrival, D - Departure
	
	char ArrDepartTime [TIME_LEN];	// Arrival or Departure time in the 
					// form hh:mm
	char status [STATUS_LEN];	// "On Time" by default
} FLIGHT;

typedef struct flightlist
{
	FLIGHT oneflight;
	struct flightlist *next;
} FLIGHTLIST;

typedef struct ticket
{
	char name [NAME_LEN];
	char Airways [AIRWAYS_LEN];	// Air India, National Airways, etc
	char flightNumber [F_LEN];	// Example NA4321
	char source [CITY_LEN];		// Source city
	char destination [CITY_LEN];	// Destination city
	char type;			// E - Economy or B - Business class
	char category;			// D - Domestic or I - International
	char D_Date [DATE_LEN];		// dd:mm:yyyy
	
	char DepartureTime [TIME_LEN];	// In the form hh:mm
} TICKET;

typedef struct boardingpass
{
	int boardId;			// Boarding pass ID
	TICKET myTicket;		// Info from the ticket
	char BoardingTime [TIME_LEN];	// In the form hh:mm 
	C_LUGGAGE_TAG myluggage [MAX_C_BAGS];
	char seatNum [SEAT_LEN];
	int GateNum;
} BOARDINGPASS;


typedef struct passenger
{
	TICKET myTicket;
	int age;
	char unique;		// Anything special about this passenger
				// 'W' - In a wheelchair, 'C' - Accompanied by a baby
				// 'V' - VIP, 'D' - Differently abled
	int cabin_baggage;	// Number of cabin bags
	int boardId;
} PASSENGER;

typedef struct passengerqueue
{
	PASSENGER passenger;
	struct passengerqueue *next;
} PASSENGERQUEUE;

typedef struct staff
{
	int staffID;			// To be generated
	char name [NAME_LEN];
	char gender;	
	char Airways [AIRWAYS_LEN];	// Air India, National Airways, etc
	char flightNumber [F_LEN];	// Example NA4321
} STAFF;

typedef struct housekeeping
{
	int hID;		// Already assigned
	char name [NAME_LEN];
	char gender;
	char h_date [DATE_LEN];	//dd:mm:yyyy
	char h_time [TIME_LEN];
	bool entryExit;		// 0 - Entering, 1 - Exiting
} HOUSEKEEPING;

typedef struct others		// Security, Vendors, etc
{
	char name [NAME_LEN];
	char gender;
	char o_Id [ID_LEN];	// Id provided by the airport
} OTHERS;