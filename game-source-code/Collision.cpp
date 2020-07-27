#include "Collision.h"


Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::checkCollision(std::vector<std::tuple<int,int>> initialPos1,std::vector<std::tuple<int,int>> initialPos2){
	
	//giving all objects some width

	int entity1_xinit=std::get<0>(initialPos1[0]);
	int entity1_xfinal=std::get<0>(initialPos1[1]);
	int entity1_yinit=std::get<1>(initialPos1[0]);
	int entity1_yfinal=std::get<1>(initialPos1[1]);
	
	int entity2_xinit=std::get<0>(initialPos2[0]);
	int entity2_xfinal=std::get<0>(initialPos2[1]);
	int entity2_yinit=std::get<1>(initialPos2[0]);
	int entity2_yfinal=std::get<1>(initialPos2[1]);
	
	
	if ((entity1_xfinal==entity1_xinit)&&(entity1_yfinal==entity1_yinit)){
		if((entity1_xinit>entity2_xfinal)&&(entity1_xinit>entity2_xfinal)){
			return false;
		}
	}
	
	//if lines are next two or above each other

	if((entity2_xinit < entity1_xinit)&&(entity2_xfinal < entity1_xinit)){
		return false;
	}
	if((entity2_xfinal > entity1_xfinal)&&(entity2_xinit > entity1_xfinal)){
		return false;
	}
	if((entity2_yinit < entity1_yinit)&&(entity2_yfinal < entity1_yinit)){
		return false;
	}
	if((entity2_yfinal > entity1_yfinal)&&(entity2_yinit > entity1_yfinal)){
		return false;
	}
	
	// if final points are the same they intersect
	if ((entity2_xfinal==entity1_xfinal)||(entity2_yfinal==entity1_yfinal)){
		return true;
	}

	if ((entity2_xinit<entity1_xinit)&&(entity2_xfinal>entity1_xfinal)
			&& (entity2_yinit<entity1_yinit)){
				return true;
			}

	if ((entity2_xinit>entity1_xinit)&&(entity2_xfinal<entity1_xfinal)
			&& (entity2_yinit>entity1_yinit)){
				return true;
			}
			
}
