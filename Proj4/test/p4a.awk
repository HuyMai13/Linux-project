BEGIN{FS=",";i=0}
{
	if($5 > $4){
		print "s/EMAIL/" $1 "/g" > "g" i ".sed"
		print "s/TITLE/" $3 "/g" > "g" i ".sed"
		print "s/FULLNAME/" $2 "/g" > "g" i ".sed"
		ii=split($2,name," ")
		print "s/NAME/" name[ii] "/g" > "g" i ".sed"
		print "s/AMOUNT/" $5 "/g" > "g" i ".sed"
		print "s/DATE/" var "/g" > "g" i ".sed"
		print "g" i ".sed " $1 >> "name.txt"
		i++
	}
}