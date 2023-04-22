/**
* Name: GridModel
* Based on the internal empty template. 
* Author: THANTHUY
* Tags: 
*/
model GridModel

global {
	int nb_preys_init <- 100;
	int nb_predators_init <- 20;
	float prey_max_energy <- 1.0;
	float prey_max_transfer <- 0.1;
	float prey_energy_consum <- 0.05;
	float predator_max_energy <- 1.0;
	float predator_energy_transfer <- 0.5;
	float predator_energy_consum <- 0.02;
	float prey_proba_reproduce <- 0.01;
	int prey_nb_max_offsprings <- 5;
	float prey_energy_reproduce <- 0.5;
	float predator_proba_reproduce <- 0.01;
	int predator_nb_max_offsprings <- 3;
	float predator_energy_reproduce <- 0.5;
	file map_init <- image_file("../includes/data/raster_map.png");
	int nb_preys -> {length(prey)};
	int nb_predators -> {length(BBox)};
	bool is_batch <- false;

	init {
		create prey number: nb_preys_init;
		create BBox number: nb_predators_init;
		ask vegetation_cell {
			color <- rgb (map_init at {grid_x,grid_y});
			food <- 1 - (((color as list) at 0) / 255);
			food_prod <- food / 100; 
		}
	}
	
//	reflex save_result when: (nb_preys > 0) and (nb_predators > 0){
//		save ("cycle: "+ cycle + "; nbPreys: " + nb_preys
//			+ "; minEnergyPreys: " + (prey min_of each.energy)
//			+ "; maxSizePreys: " + (prey max_of each.energy) 
//	   		+ "; nbPredators: " + nb_predators           
//	   		+ "; minEnergyPredators: " + (predator min_of each.energy)          
//	   		+ "; maxSizePredators: " + (predator max_of each.energy)) 
//	   		to: "results.txt" rewrite: (cycle = 0) ? true : false;
//	}
	
//	reflex stop_simulation when: ((nb_preys = 0) or (nb_predators = 0)) and !is_batch {
//		do pause;
//	} 
}

species generic_species {
	float size <- 1.0;
	rgb color;
	float max_energy;
	float max_transfer;
	float energy_consum;
	float proba_reproduce;
	int nb_max_offsprings;
	float energy_reproduce;
//	image_file my_icon;
	vegetation_cell my_cell <- one_of(vegetation_cell);
	float energy <- rnd(max_energy) update: energy - energy_consum max: max_energy;

	init {
		location <- my_cell.location;
	}

	reflex basic_move {
		my_cell <- choose_cell();
		location <- my_cell.location;
	}

	reflex eat {
		energy <- energy + energy_from_eat();		
	}

	reflex die when: energy <= 0 {
		do die;
	}

	reflex reproduce when: (energy >= energy_reproduce) and (flip(proba_reproduce)) {
		int nb_offsprings <- rnd(1, nb_max_offsprings);
		create species(self) number: nb_offsprings {
			my_cell <- myself.my_cell;
			location <- my_cell.location;
			energy <- myself.energy / nb_offsprings;
		}

		energy <- energy / nb_offsprings;
	}

	float energy_from_eat {
		return 0.0;
	}

	vegetation_cell choose_cell {
		return nil;
	}

	aspect base {
		draw circle(size) color: color;
	}

//	aspect icon {
//		draw my_icon size: 2 * size;
//	}

	aspect info {
		draw square(size) color: color;
		draw string(energy with_precision 2) size: 3 color: #black;
	}
}

species prey parent: generic_species {
	rgb color <- #blue;
	float max_energy <- prey_max_energy;
	float max_transfer <- prey_max_transfer;
	float energy_consum <- prey_energy_consum;
	float proba_reproduce <- prey_proba_reproduce;
	int nb_max_offsprings <- prey_nb_max_offsprings;
	float energy_reproduce <- prey_energy_reproduce;
//	image_file my_icon <- image_file("../includes/data/sheep.png");

	float energy_from_eat {
		float energy_transfer <- 0.0;
		if(my_cell.food > 0) {
			energy_transfer <- min([max_transfer, my_cell.food]);
			my_cell.food <- my_cell.food - energy_transfer;
		} 			
		return energy_transfer;
	}

	vegetation_cell choose_cell {
		return (my_cell.neighbors2) with_max_of (each.food);
	}
}

species BBox parent: generic_species {
	geometry shape<-cube(1); 
	rgb color <- #red;
	float max_energy <- predator_max_energy;
	float energy_transfer <- predator_energy_transfer;
	float energy_consum <- predator_energy_consum;
	float proba_reproduce <- predator_proba_reproduce;
	int nb_max_offsprings <- predator_nb_max_offsprings;
	float energy_reproduce <- predator_energy_reproduce;
//	image_file my_icon <- image_file("../includes/data/wolf.png");

	float energy_from_eat {
		list<prey> reachable_preys <- prey inside (my_cell);
		if(! empty(reachable_preys)) {
			ask one_of (reachable_preys) {
				do die;
			}
			return energy_transfer;
		}
		return 0.0;
	}

	vegetation_cell choose_cell {
		vegetation_cell my_cell_tmp <- shuffle(my_cell.neighbors2) first_with (!(empty(prey inside (each))));
		if my_cell_tmp != nil {
			return my_cell_tmp;
		} else {
			return one_of(my_cell.neighbors2);
		}
	}
}

grid vegetation_cell width: 50 height: 50 neighbors: 4 {
	float max_food <- 1.0;
	float food_prod <- rnd(0.01);
	float food <- rnd(1.0) max: max_food update: food + food_prod;
	rgb color <- rgb(int(255 * (1 - food)), 255, int(255 * (1 - food))) update: rgb(int(255 * (1 - food)), 255, int(255 * (1 - food)));
	list<vegetation_cell> neighbors2 <- (self neighbors_at 2);
}

experiment grid_model type:gui {

	float minimum_cycle_duration <- 0.15#second;
 
	output {
		display main_display {
			grid vegetation_cell border: #black;
			species prey aspect: base;
			species BBox aspect: base;
		}
 }
}


