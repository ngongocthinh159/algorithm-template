
// time: if we have n bits => O(3^n) for iterating all submasks of all masks
// https://cp-algorithms.com/algebra/all-submasks.html

// iterate over all masks
for (int mask = 0; mask < (1<<n); mask++){
	F[mask] = A[0];

    // iterate over all the submask of the current mask
    for(int submask = mask; ; submask = (submask - 1) & mask){
        if (submask == 0) // Not use submask = 0
            break;
        
    	F[mask] += A[i];
    }
}


// iterate over all masks
for (int mask = 0; mask < (1<<n); mask++){
	F[mask] = A[0];

    // iterate over all the submask of the current mask
    for(int submask = mask; ; submask = (submask - 1) & mask){
    	F[mask] += A[i];

        if (submask == 0) // Use submask = 0
            break; 
    }
}


