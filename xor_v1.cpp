#include <iostream>
#include <string.h>

using namespace std;

struct Node {
    long long data;
    Node* link;
};

class xor_v1 {

      private:
            char *comand;
            Node *head;
            Node *feet;
            Node *actualNode;
            Node *prevNode;
      public:
            xor_v1() {

                  this->head = nullptr;
                  this->feet = nullptr;
                  this->actualNode = nullptr;
                  this->prevNode = nullptr;
                  while (true)
                        this->comandListener();
            }

            ~xor_v1() {}

            void comandListener() {

                  this->comand = new char[64];
                  scanf("%63s", &this->comand[0]);

                  if (!strcmp(this->comand, "ACTUAL")) {

                        this->actual();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "NEXT")) {

                        this->next();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "PREV")) {

                        this->prev();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "DEL_BEG")) {

                        this->del_beg();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "DEL_END")) {

                        this->del_end();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "DEL_ACT")) {

                        this->del_act();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "PRINT_FORWARD")) {

                        this->print_forward();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "PRINT_BACKWARD")) {

                        this->print_backward();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "ADD_BEG")) {

                        this->add_beg();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "ADD_END")) {


                        this->add_end();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "ADD_ACT")) {

                        this->add_act();
                        delete [] this->comand;
                        return;
                  }
                  if (!strcmp(this->comand, "DEL_VAL")) {

                        this->del_val();
                        delete [] this->comand;
                        return;
                  }
            }

            void actual() {

                  if(this->actualNode == nullptr) {

                        printf("NULL\n");
                        return;
                  }

                  printf("%lld", this->actualNode->data);
            }

            void next() {

                  Node *next;

                  next = this->XOR(this->prevNode, this->actualNode->link);

                  this->prevNode = this->actualNode;
                  this->actualNode = next;

                  printf("%lld", this->actualNode->data);
            }

            void prev() {

                  Node *prev;

                  prev = this->XOR(this->actualNode, this->prevNode->link);

                  this->actualNode = this->prevNode;
                  this->prevNode = prev;

                  printf("%lld", this->actualNode->data);
            }

            void add_beg() {

                  long long N;
                  scanf("%lld", &N);

                  Node* newNode = new Node();
                  newNode->data = N;

                  newNode->link = this->XOR(this->head, nullptr);

                  if (this->head)
                        this->head->link = this->XOR(newNode, this->XOR(this->head->link, nullptr));

                  if(this->actualNode == nullptr)
                        this->actualNode = newNode;

                  this->head = newNode;
            }

            void add_end() {

                  long long N;
                  scanf("%lld", &N);

                  Node* newNode = new Node();
                  newNode->data = N;

                  newNode->link = this->XOR(nullptr, this->feet);

                  if (this->feet)
                        this->feet->link = this->XOR(this->XOR(nullptr, this->feet->link), newNode);

                  if(this->actualNode == nullptr)
                        this->actualNode = newNode;

                  this->feet = newNode;
            }

            void add_act() {

                  long long N;
                  scanf("%lld", &N);

                  Node* newNode = new Node();
                  newNode->data = N;
                  newNode->link = this->XOR(this->prevNode, this->actualNode);

                  this->prevNode->link = this->XOR(this->XOR(this->prevNode->link, this->actualNode), newNode);
                  this->actualNode->link = this->XOR(this->XOR(this->prevNode, this->actualNode->link), newNode);
                  this->prevNode = newNode;
            }

            void del_beg() {

                  Node *headNext = this->XOR(this->head->link, nullptr);

                  if(headNext != nullptr)
                        headNext->link = this->XOR(this->XOR(headNext->link, this->head), nullptr);

                  delete [] this->head;

                  this->head = headNext;
            }

            void del_end() {

                  Node *feetPrev = this->XOR(this->feet->link, nullptr);

                  if(feetPrev != nullptr)
                        feetPrev->link = this->XOR(this->XOR(feetPrev->link, this->feet), nullptr);

                  delete [] this->feet;

                  this->feet = feetPrev;
            }

            void del_val() {

                  long long N;
                  scanf("%lld", &N);

                  Node* curr = this->head;
                  Node* prev = nullptr;
                  Node *next;

                  for(; curr != nullptr ;) {

                        next = this->XOR(prev, curr->link);
                        if(curr->data == N){

                              if(prev != nullptr)
                                    prev->link = this->XOR(this->XOR(prev->link, curr), next);

                              if(next != nullptr)
                                    next->link = this->XOR(this->XOR(next->link, curr), prev);

                              delete [] curr;

                              curr = next;
                              continue;
                        }
                        prev = curr;
                        curr = next;
                  }
            }

            void del_act() {

                  Node *nextNode = this->XOR(this->prevNode, this->actualNode->link);

                  this->prevNode->link = this->XOR(this->XOR(this->prevNode->link, this->actualNode), nextNode);
                  if(nextNode != nullptr)
                        nextNode->link = this->XOR(this->XOR(nextNode->link, this->actualNode), this->prevNode);

                  delete [] this->actualNode;

                  this->actualNode = this->prevNode;
                  this->prevNode = this->XOR(this->actualNode->link, nextNode);
            }

            void print_forward() {

                  Node* curr = this->head;
                  Node* prev = nullptr;
                  Node *next;

                  for(; curr != nullptr ;) {

                        printf("%lld", curr->data);

                        next = this->XOR(prev, curr->link);

                        prev = curr;
                        curr = next;
                  }
            }

            void print_backward() {

                  Node *curr = this->feet;
                  Node *next = nullptr;
                  Node *prev;

                  for(; curr != nullptr ;) {

                        printf("%lld", curr->data);

                        prev = this->XOR(next, curr->link);

                        next = curr;
                        curr = prev;
                  }
            }

            Node* XOR(Node* x, Node* y) {

                  return (Node*)((uintptr_t)(x) ^ (uintptr_t)(y));
            }
};

int main() {

      xor_v1 List;

      return 0;
}