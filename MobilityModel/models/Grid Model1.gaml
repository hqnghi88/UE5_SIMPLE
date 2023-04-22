/**
* Name: GridModel
* Based on the internal empty template. 
* Author: THANTHUY
* Tags: 
*/


model GridModel

/* Insert your model definition here */
global {
	 
	geometry shape <- square(2000);
	
	int zz<-100;
	
	init{	 
//		create BBox number:2 ;
	}
	reflex ss when: length(BBox)<500 and flip(0.05){
		create BBox{
			location<-{location.x,location.y,zz};
		}
	}
 
}

 species BBox skills:[moving]{
	geometry shape<-cube(10);
	rgb color<-rnd_color(255);
	reflex s{
		do wander speed:0.1;
	}
 }

experiment grid_model type:gui {

	float minimum_cycle_duration <- 0.01#second;

	output{
		
		display main_display type:3d axes:false{
			species BBox;
		}	
	}
}


