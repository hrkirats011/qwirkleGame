#include <iostream>
#include <random>

#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   size = 0;

}

LinkedList::~LinkedList() {
  
}



int LinkedList::getSize(){
   return size;
}



void LinkedList::addBack(std::shared_ptr<Tile> tile) {
   
   std::shared_ptr<Node> newNode = std::make_shared<Node>(tile, nullptr);
   
   if (head == nullptr){
      head = newNode;
   }
   else{
      std::shared_ptr<Node> current = head;
      while(current->next != nullptr){
         current = current->next;
      }
      current->next = newNode;
   }
   size+=1;
}

std::shared_ptr<Tile> LinkedList::removeFront(){

   std::shared_ptr<Tile> return_val = nullptr;
   std::shared_ptr<Node> newHead = nullptr;

   if (head != nullptr){
      newHead = head->next;
      return_val = head->tile;
      head = newHead; 
      size-=1;
   } 
   return return_val;
   
}

std::shared_ptr<Tile> LinkedList::remove(int index){
   
   std::shared_ptr<Tile> return_val = nullptr;
   
   if(index >= 0 && index < size){
      if (head != nullptr){

          int counter = 0;
          std::shared_ptr<Node> current = head;
          std::shared_ptr<Node> previous = nullptr;

         while(counter != index){
            previous = current;
            current = current->next;
            counter++;
            }

            if(previous == nullptr){
                head = current->next;
            }else{
                previous->next = current->next;
            }
            
            //delete current;
            return_val = current->tile;
      } 
      size -= 1;
   } return return_val;
}





int LinkedList::getIndex(std::shared_ptr<Tile> t){
   
   int return_val = -1;
   int counter = 0;
   bool found = false;
   
      if(head != nullptr){
         std::shared_ptr<Node> current = head;
         while(current!=nullptr && found==false){
            
            if (current->tile->compareTile(t)){
               return_val = counter;  
               found = true; 
            }
            current = current->next;
            counter++;
         }
      } return return_val;
}



std::shared_ptr<Node> LinkedList::getNode(int index){
   
   std::shared_ptr<Node> returnVal = nullptr;
   
   if(index >= 0 && index < size){
      int counter = 0;
      std::shared_ptr<Node> current = head;

      while(counter < index){
         current = current->next;
         counter++;
      }
      returnVal = current;
   }
   return returnVal; 

}

int LinkedList::getTileIndex(std::string str){
   
  
      int return_val = -1;
      int counter = 0;
      bool found_tile = false;
      std::shared_ptr<Node> current = head;

      while(current!=nullptr && found_tile == false){
         if(current->tile->hasLabel(str)){
            found_tile = true;
            return_val = counter;
         }
         current = current->next;
         counter++;
      }
   return return_val; 
}

bool LinkedList::containsTile(std::shared_ptr<Tile> tile){
   
   bool returnVal = false;

   if(head != nullptr){
      std::shared_ptr<Node> current = head;
      while(current != nullptr){
         if(current->tile->compareTile(tile)){
            returnVal = true;
         }
         current = current->next;
      }
   }
   return returnVal;
}


void LinkedList::printTiles(){

   if (head != nullptr){
      std::shared_ptr<Node> current = head;
      while(current != nullptr){
         std::cout << " " << current->tile->getColour() <<
                     current->tile->getShape() << " ";
         current = current->next;
      }
      std::cout << std::endl;
   }
}

std::string LinkedList::getAllTiles(){
   std::string return_val = "";
   if (head != nullptr){
      std::shared_ptr<Node> current = head;
      while(current != nullptr){
         return_val += current->tile->getColour() +
                       std::to_string(current->tile->getShape()) + ",";
         current = current->next;
      }
   } return return_val;
}

void LinkedList::shuffle(){ 

   if (head != nullptr){

      int counter = size;
      std::random_device engine;
      // std::default_random_engine engine(10);

      while(counter > 0){
         
         std::uniform_int_distribution<int> uniform_dist(0, counter - 1); 
         int rand_num = uniform_dist(engine);
         
         std::shared_ptr<Tile> rand_tile = getNode(rand_num)->tile;
         std::shared_ptr<Tile> copy = std::make_shared<Tile>(*rand_tile);
         
         addBack(copy);
         remove(rand_num);
         
         counter-=1;
      }
   }
}