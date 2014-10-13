/* module file */

extern int bar(int param);

/* Req 101 – Foo shall return parameter2 if half of parameter2 is more than parameter1. */
/* Req 102 – Foo shall return parameter1 if parameter1 is greater or equal to half of parameter2. */
/* Req 103 – Foo shall return zero (0) if either parameter is negative. */
int foo (int param1, int param2)
{
	int err, retval;

	if ((param1 < 0) || (param2 < 0))
	{
		retval = 0;
	}
	else
	{
		/* Call the divide by 2 function */
		err = bar(param2);
		if (err > param1)
		{
			retval = param2;
		}
		else
		{
			retval = param1;
		}
	}
	return(retval);
}
