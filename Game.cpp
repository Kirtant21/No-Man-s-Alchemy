//Title: Game.cpp
//Author: Kirtan Thakkar
//Date: 3/5/2021
//Description: this is a function class of Game.h for the game "No Man's Alchemy
//Class/section: CMSC 202, 10 (SP21)

#include <iostream>
#include "Game.h"
#include <string>
using namespace std;



Game::Game(){

  string input;

  LoadMaterials(); //loads the materials into the array
   
   cout << "\n\nWhat would you like to name your Ship?: ";
   cin >> input;

  
   m_myShip.SetName(input);

   cout << "\n\tyour Ship name is " <<  m_myShip.GetName() << endl;


   DisplayMaterials(); //displays the game
   cout << SIGNOFF << endl;
   
 }


void Game::LoadMaterials(){

  int index = 0;
  
  ifstream inputFile;
  


   inputFile.open(PROJ2_DATA);
  
   if (inputFile.is_open()){ //Reading the data

     while (inputFile.is_open()){

       getline(inputFile, m_materials[index].m_name, ',');

       getline(inputFile,  m_materials[index].m_type, ',');

       getline(inputFile,  m_materials[index].m_material1, ',');

       getline(inputFile,  m_materials[index].m_material2, '\n');



	  index++;

	  if (index == PROJ2_SIZE)
	    {
	      inputFile.close();
	    }
	      
	  
     }

     StartGame();
     cout << "\t" << index << " materials loaded. " << endl;


     
    }else{

      cout << "unable to open the file! " << endl;
    }


   for (int i = 0; i <= PROJ2_SIZE -1; i++)
     {

       m_myShip.AddMaterial(m_materials[i]); 

     }
   
   
}


void Game::StartGame(){


  GameTitle();
}

void Game::DisplayMaterials(){
  
  int choice;
  string name1, name2;
  bool Quit = false;

  do{

    choice = MainMenu();
    
    switch(choice) // manages the 5 choices.
    {
    case 1:

      for(int i = 0; i <= PROJ2_SIZE; i++)
	{
	  cout << m_myShip.GetMaterial(i).m_name << ", " << m_myShip.GetMaterial(i).m_quantity << endl;

	}

      break;

    case 2:

      SearchMaterials();

      break;

    case 3:

      CombineMaterials();

      break;

    case 4:

      CalcScore ();


      break;

    case 5:

      cout << EXIT << endl;
      Quit = true;

      break;

    default:

      if (choice <= 0 || choice > 5)
	{
	  cout << "\n\t    ****Invalid choice***\n Please enter a valid integer(between 1 - 5)" << endl;

	}
    }

  
}while (!Quit);

  

}
  

int Game::MainMenu(){


  int choice;



    
  cout <<"\n what would you like to do? " << endl;
  cout <<" 1. Display your Ship's Materials " << endl;
  cout <<" 2. search for Raw Materials " << endl;
  cout <<" 3. Attempt to Merge Materials " << endl;
  cout <<" 4. see Score " << endl;
  cout <<" 5. Quite  " << endl;

  cin >> choice;
 
	  
  return choice;
}

void Game::SearchMaterials(){

  int randomIndex;

  
  do{

    randomIndex = rand() % PROJ2_SIZE;
    
   
  }while(m_materials[randomIndex].m_type != "raw");// this loop checks if the materials if raw or not.

      cout << m_materials[randomIndex].m_name << " found! " << endl;  
    
      m_myShip.IncrementQuantity(m_materials[randomIndex]); // increments the searched raw materials 
	    

 
}

void Game::CombineMaterials(){
  
  int index = 0;
  string name1, name2;


  
  RequestMaterial(index); //Requests materials

  name1 = m_myShip.GetMaterial(index).m_name; // stores the name of user's first choice of the material as a string
  
  RequestMaterial(index);
   
  name2 =  m_myShip.GetMaterial(index).m_name; // stores the name of user's second choice of the material as a string

  index = SearchRecipes(name1, name2); // finds the recipe and store the index of the item.

  
  if(index != 0)
    {
      cout << " you have made " << m_materials[index].m_name;
      
      m_myShip.IncrementQuantity(m_materials[index]); // increaments the items made by combining two materials 

    }else{

    cout << "no match recipes found for these two combinations" << endl;


  }
 

}

void Game::RequestMaterial(int &choice){
  
  int input;
  bool askAgain = false;

  do{

  cout << "Which materials would you like to marge? " << endl;
  cout << "To list known materials enter -1 " << endl;
  cin >> input;

  
  if (input == -1)
    {

      for(int i = 0; i <= PROJ2_SIZE; i++)
	{
	  cout << m_myShip.GetMaterial(i).m_name << ", " << m_myShip.GetMaterial(i).m_quantity << endl;

	}

      DisplayMaterials();
      
    }else if (input <= PROJ2_SIZE && input != 0){
    
  *&choice = input;

    askAgain = false;

  }else {

    cout << "error: ** Please enter a valid integer **" << endl;
    askAgain = true;

  }


    
  }while(askAgain);
    
    // m_myShip.CheckMaterial(m_material[&choice])
}

int Game::SearchRecipes (string str1, string str2){

  Material mat1;
  Material mat2;

  
  for(int k = 0; k <= PROJ2_SIZE; k++)
    {
      if(m_materials[k].m_name == str1)
	{
	  mat1 = m_materials[k];

	}

      if (m_materials[k].m_name == str2)
	{
	  mat2 = m_materials[k];

	}
      
    }

  if(m_myShip.CheckQuantity(mat1, mat2))
    {
     
  for(int i = 0; i <= PROJ2_SIZE; i++)
    {

      if((m_materials[i].m_material1 == str1 && m_materials[i].m_material2 == str2) || (m_materials[i].m_material1 == str2 && m_materials[i].m_material2 == str1)) // this if statments takes both names and manages their order while finding the recipe.
        {

	  if(m_materials[i].m_type == "unique")// checks if the material is unique or not
	    {

	      if(m_myShip.GetMaterial(i).m_quantity == 1)// if the material already exisit in the player's ship.
		{
		  cout << "\n\t Note: Since  " << m_myShip.GetMaterial(i).m_name << " is a unique material,\n you can only have one of this kind, you may find other common/uncommon or unique materials \n to to merge and create uniuq materials for your ship.\n\t Good Luck, Happy hunting!" << endl;

		}else{
		
		m_myShip.DecrementQuantity(mat1); // decrements the quantity of the unique material
			m_myShip.DecrementQuantity(mat2);

			
		return i;
	      }
	      
	    }else{

	    m_myShip.DecrementQuantity(mat1); // decrements the quantity of the non-unique materials
	    m_myShip.DecrementQuantity(mat2);
	    
	    return i;
	  }
	}
    }

    }else{

    cout << "** Note: the great ship of " << m_myShip.GetName() << " does not have enough materials to marge!\n\t ** Please continue searching for more raw materials. **" << endl;

      }
    

  return 0;
}

void Game::CalcScore (){


  
  m_myShip.IncRank();
  
  cout <<" *** No Man's Alchemy *** " << endl;
  cout <<" The Great Ship of " << m_myShip.GetName() << endl;
  cout << " Ship Rank: " <<  m_myShip.GetRank() << endl;

}


