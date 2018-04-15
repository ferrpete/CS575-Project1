// Weight.cpp
// Determines the weight for each node

#define XMIN	 0.
#define XMAX	 3.
#define YMIN	 0.
#define YMAX	 3.

double Weight( int iu, int iv )
{
	
	// To calculate the weight, we're going to first convert the node numbers
	// into Cartesian coordinates.  The domain is from 0 to 3 for both x and y.
	
	float u = (float)(XMAX * iu) / (float)(NUMNODES-1);
	float v = (float)(YMAX * iv) / (float)(NUMNODES-1);
	
	// Next we check if the node belongs to a vertical edge
	
	if (u == 0 || u == 1)
	{
		
		// From here, we check to see if the node belongs to a corner on the square
		// domain.
		
		if (v == 0 || v == 1)
		{
			
			// The node receives a quarter weight since it only influences a quarter
			// tile on the domain.
			
			return 0.25;
			
		}
		
		else{
			
			// The node receives a half weight since it only influences a half tile on
			// the domain.
			
			return 0.5;
			
		}
		
	}
	
	// If the node does not belong to a vertical edge, it either belongs to a horizontal
	// edge or the interior of the domain.
	
	else
	{
		
		// Check to see if node is on horizontal edge.
		
		if (v == 0 || v == 1)
		{
			
			// The node receives a half weight since it only influences a half tile on
			// the domain.
			
			return 0.5;
			
		}
		else{
			
			// The node lies on the interior of the domain and thus receives a full weight.
			
			return 1;
			
		}
		
	}
	
}