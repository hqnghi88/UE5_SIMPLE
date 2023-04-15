/**
* Name: GridModel
* Based on the internal empty template. 
* Author: THANTHUY
* Tags: 
*/


model GridModel

/* Insert your model definition here */
global {
	 
	geometry shape <- square(100);
	
	
	
	init{	 
		create BBox number:5;
	}
 
}

 species BBox skills:[moving]{
	geometry shape<-cube(10);
	rgb color<-rnd_color(255);
	reflex s{
		do wander;
	}
 }

experiment grid_model type:gui autorun:true{

	float minimum_cycle_duration <- 0.5#second;

	output{
		
		display main_display type:3d axes:false{
			species BBox;
		}	
	}
}


