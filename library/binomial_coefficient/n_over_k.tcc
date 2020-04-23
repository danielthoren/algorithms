template <typename T>
T n_over_k(T n, T k, std::vector<std::vector<T>>& triag)
{
    if (triag.size() > n)
	return triag[n][k];
    
    T i, j; 
  
    for (i = triag.size(); i <= n; i++) 
    {
	triag.push_back( std::vector<T>() );
	
        for (j = 0; j <= i; j++) 
        { 
            if (j == 0 || j == i)
	    {
                triag[i].push_back(1);
	    }
            else
	    {
                triag[i].push_back( triag[i - 1][j - 1] + 
				    triag[i - 1][j] );
	    }
        } 
    } 
  
    return triag[n][k];
}

template <typename T>
T n_over_k(T n, T k)
{
    T curr = 1;
    for (T column{1}; column <= k; column++)
    {
	curr *= n - (k - column);
	curr /= column;
    }
    return curr;
}
