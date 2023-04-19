/**
* Name: GridModel
* Based on the internal empty template. 
* Author: THANTHUY
* Tags: 
*/


model GridModel

/* Insert your model definition here */
global {
	 
	geometry shape <- square(4000);
	
	
	
	init{	 
		create BBox number:10;
	}
	reflex ss when: flip(0.0001){
		create BBox;// number:rnd(10);
	}
 
}

 species BBox skills:[moving]{
	geometry shape<-cube(1);
	rgb color<-rnd_color(255);
	reflex s{
		do wander speed:0.1;
	}
 }

experiment grid_model type:gui {

	//float minimum_cycle_duration <- 0.5#second;

	output{
		
		display main_display type:3d axes:false{
			species BBox;
		}	
	}
}


