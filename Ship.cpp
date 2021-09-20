//Title: Ship.cpp
//Author: Kirtan Thakkar
//Date: 3/5/2021
//Description: this is a function class of Ship.h for the game "No Man's Alchemy
//Class/section: CMSC 202, 10 (SP21)


#include "Ship.h"
#include "Material.h" //Include for the material struct


Ship ::Ship(){

  m_shipRank = 'D';
  m_numMaterials = 0;

  
}

Ship ::Ship(string name){

  m_shipName = name;
   

}

  
string Ship::GetName(){

  return m_shipName;
}

void Ship::SetName(string name){


  m_shipName = name;

}

int Ship::CheckMaterial(Material newMaterial){

  for (int i = 0; i <= PROJ2_SIZE; i++) // finds the newMaterial in the m_myMaterial[]
    {
      if(m_myMaterials[i].m_name == newMaterial.m_name)
	{
	  if(m_myMaterials[i].m_quantity > 0) // if found check quantity 
	    {
	      return i;//returns the index
	      
	    }else{

	    return -1; 
	  }
	}
    }
	     
  return 0;
}

void Ship::AddMaterial(Material newMaterial){ // populates the m_myMaterial []


  m_numMaterials += 1;

  newMaterial.m_quantity = 0;
  m_myMaterials[m_numMaterials] = newMaterial;

}

void Ship::IncrementQuantity(Material newObj){

  for (int i = 0; i <= PROJ2_SIZE; i++)
    {
      if(newObj.m_name == m_myMaterials[i].m_name)

	{
	   m_myMaterials[i].m_quantity++; 
	 
	}
    }
}

bool Ship::DecrementQuantity(Material newObj){

  
  for (int i = 0; i <= PROJ2_SIZE; i++) // finds newObj in the m_myMaterials[]
    {
      if(newObj.m_name == m_myMaterials[i].m_name) 
	{
	  if(m_myMaterials[i].m_quantity == 0) // if found, checks if the quantity is 0
	    {
	      return false;
	      
	    }else{

	    m_myMaterials[i].m_quantity--; // if quantity is not 0, then Decrements the quantity
	 
	      return true;
	  }

	}
    }
  
  return true;
}

bool Ship::CheckQuantity(Material newMat1, Material newMat2){

  bool audit = false, audit2 = false;

  
  for(int a = 0; a <= PROJ2_SIZE; a++) // runs and finds newMat1 in m_myMaterials[]
    {
      if (m_myMaterials[a].m_name == newMat1.m_name)
	{
	  if (m_myMaterials[a].m_quantity > 0) // checks quantity 
	    {
	      audit = true;
	    }else{audit = false;}
	  
	}
    }

  for(int b = 0; b <= PROJ2_SIZE; b++)// runs and finds newMat2 in m_myMaterials[]
    {
      if (m_myMaterials[b].m_name == newMat2.m_name)
	{
	  if(m_myMaterials[b].m_quantity > 0) // checks quantity 
	    {
	      audit2 = true;

	    }else{audit2 = false;}

	}

    }


  if(audit && audit2)
    {
        return true;
    }else { return false; }

}

Material Ship::GetMaterial(int num){

  return m_myMaterials[num];


}

void Ship::IncRank()
{

  int addUp = 0;
  
  for (int i = 0; i <= PROJ2_SIZE; i++) // runs and checks if there is/are any unique material(s) on the ship
    {
      if(m_myMaterials[i].m_type == "unique")// Ranks based of how many unique materials are found 
	{
	  addUp += 1;
	}
    }

  
      switch(addUp)
	{
	case 1:
	  m_shipRank = 'C';
	    break;

	case 2:
	  m_shipRank = 'B';
	      break;

	case 3:
	  m_shipRank = 'A';
	      break;

	case 4:
	  m_shipRank = 'S';
	      break;

	}
      
}


char Ship::GetRank(){


  return m_shipRank;
}

