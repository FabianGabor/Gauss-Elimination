function appendText(x) {
    var i = 0;
    $("#solution").empty();
    $(x).each(function() {
        $("#solution").append('<li class="stat">x<span class="h6">' + i + "</span> = " + '<span class="stat">' + x[i] + '</span>' + '</li>');
        i++;
    })
} 


function Gauss() {
	var map = [];
	var numItems = $('.equals').length;	
	var a = [[]];
	var b = [];
    var i = j =0;
    var x = [0,0,0];
    var sum = 0;

	$(".unknown").each(function() {		
		map.push($(this).val());		
    });
    
    $(".equals").each(function() {		
		b.push($(this).val());		
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

    console.log(a);
    console.log(b);

	
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

    for (i=n-1; i>=0; i--)
    {        
        sum = b[i];
        for (j=0; j<n; j++)
        {
            sum -= a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
    }

	//console.log(a);
    //console.log(b);
    
    console.log("Megoldás: ");
    for (i=0; i<n; i++)
    {
        console.log("x",i,"=",x[i]);
    }
    appendText(x);
    

}