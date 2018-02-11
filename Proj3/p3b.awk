BEGIN{printf "Name\t\tFlight\t\tSeats Total Cost\n"}
{
	if($1 == "CUST")
		name=$NF;
	if($1 == "RESERVE"){
		printf name"\t\t"$2"\t"$3"\t"$4"\n";
		total+=$4;
		flight[$2]+=$3;
	}
	if($1 == "ENDCUST"){
		printf "\t\t\t\tTotal\t%.2f\n",total;
		total=0;
	}
}
END{
	printf "Flight\tTotal Seats\n"
	for(f in flight)
		printf f"\t"flight[f]"\n";
}