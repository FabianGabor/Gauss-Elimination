function Gauss() {
	var map = [];
	var numItems = $('.input-group-field').length;	
	var a = [[]];
	var b = [8,1,3];
	var i = j =0;

	$(".input-group-field").each(function() {		
		map.push($(this).val());		
	});

	var n = Math.sqrt(map.length);
	
	for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
			a[i][j] = map[i*n + j];
		}
		if (i<n-1) a.push(new Array());
	}

	const a_original = a;
	console.log(a_original);

	/*
	for (k=0; k<n-1; k++)
    {
        for (i=k+1; i<n; i++)
        {
            mult = a[i][k];
            lead = a[k][k];

            b[i] *= lead;
            b[i] -= mult * b[k];

            for (j=k; j<n; j++)
            {
                a[i][j] *= lead;
                a[i][j] -= mult * a[k][j];
            }
        }        
    }
	*/

	//console.log(map);
	console.log(a);
	console.log(b);
}