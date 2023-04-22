/**
* Name: prey predator
* Author: HUYNH Quang Nghi
* Description: This is a simple comodel serve to demonstrate the mixing behaviors of preyPredator with the Ants. Ants are the prey, fleeing from Predators, when they are not chasing, they try to do job of the ants.
* Tags: comodel
*/
model prey_predator


global
{
	geometry shape <- square(8000);
	float perceipt_radius <- 1000.0;
	int preyinit <- 150;
	int predatorinit <- 3;
	list<agent> lstPredator;// <- list<agent> (predator);
	list<agent> lstPrey; //<- list<agent> (prey);
	init
	{
		create BBox number: preyinit;
		create predator number: predatorinit;
		lstPredator <- list<agent> (predator);
		lstPrey <- list<agent> (BBox);
	}

}

species generic_species skills: [moving]
{
	float speed <- 10.0;
	point goal;
	bool is_chased <- false;
	reflex live_with_my_goal
	{
		if (goal != nil)
		{
//			do wander speed: speed;
			do goto target: goal speed: speed;
		} else
		{
			do wander amplitude:359.0 speed: speed;
		}

	}

}

species BBox parent: generic_species
{
	geometry shape <- circle(100);
	float speed <- 2.0;
	rgb color <- # green;
	reflex fleeing
	{
		if (length((lstPredator where (each != nil and !dead(each) and each distance_to self < perceipt_radius))) > 0)
		{
			speed <- 15.0;
			is_chased <- true;
			color <- # lime;
			if (goal = nil)
			{
				agent a <- any(((lstPrey where (each != nil and !dead(each) and !generic_species(each).is_chased))));
				if (a != nil and !dead(a))
				{
					if (flip(0.5))
					{
						goal <- a.location;
					} else
					{
						goal <- any_location_in(world.shape);
					}

				} else
				{
					goal <- any_location_in(world.shape);
				}

			}

		}

		if (goal != nil and self.location distance_to goal < 50)
		{
			goal <- nil;
		}

		if (length((lstPredator where (each != nil and !dead(each))) where (each distance_to self <= perceipt_radius)) = 0)
		{
			is_chased <- false;
			color <- # green;
			speed <- 2.0;
		}

	}

	aspect default
	{
		draw shape color: color;
	}

}

species predator parent: generic_species
{
	geometry shape <- triangle(300);
	rgb color <- # red;
	reflex hunting
	{
		if (goal = nil)
		{
			list tmp <- (lstPrey where (!dead(each) and each.shape distance_to self.shape < perceipt_radius));
			if (length(tmp) > 0)
			{
				agent a <- first(tmp sort (each.shape distance_to self.shape));
				if (a = nil)
				{
					a <- any((lstPrey where (!dead(each))));
				}

				if (a != nil)
				{
					speed <- 25.0;
					goal <- a.location;
				}

			}

		} else if ((self.location distance_to goal < 25))
		{
			ask lstPrey where (!dead(each) and each.location distance_to goal < 25)
			{
				do die;
			}

			goal <- nil;
			speed <- 15.0;
		}

	}

	aspect default
	{
		draw circle(perceipt_radius) color: # pink wireframe: true;
		draw shape color: color rotate: 90 + my heading;
	}

}

experiment grid_model type:gui 
{
	
	float minimum_cycle_duration <- 0.01#second;
	output
	{
		display main_display
		{
			species BBox;
			species predator;
		}

	}

}