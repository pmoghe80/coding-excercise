#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithms>

/* Message HDR Class:
 * 1) srcID:  Node sending Membership List
 * 2) destID: Node receiving MemberShip List
 * 3) GenNo:  Monotonically incrementing generation number
 */
class MessageHdr {
        int srcID;
	int dstID;
        int GenNo;
public:
	SetSrcID(int);
	SetDstID(int);
	SetGenNo(int);
};

/* Message class which contains Message HDR and payload.
 * It contains operation to create, send and receive message also;
 */
class Message {
	MessageHdr h;
	int        size;
	void       *payload;
public:
        Message (void *data, int size);
	SendMessage(int id, Message *);
};

class Node {
private:	
	vector<int> timeStVector;
	int         memberID;
        int         currGenNo;
public:
	Node(int memberID, int gennum);
	
        	
