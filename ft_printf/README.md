# ft_printf

My project completes the mandatory part:

• You have to recode the libc’s printf function.

• Your function will be called ft_printf and will be prototyped similarly to printf.

• You won’t do the buffer management in the printf function.

• You have to manage the following conversions: csp

• You have to manage the following conversions: diouxX with the following flags: hh, h, l and ll.

• You have to manage the following conversion: f with the following flags: l and L.

• You must manage %%

• You must manage the flags #0-+ and space

• You must manage the minimum field-width

• You must manage the precision

And bonuses:

1)	Long arithmetic	(can print whole LDBL_MIN with precision .16382)

2)	*/.* (filling the width/pricision with arguments from va_args)

3)	n$ (printing the n-th element from va_args)

4)	*n$/.*n$ (filling the width/pricision with n-th argument from va_args)

5)	j/z flags (working as priority ll flag)

6)	Colours

		Red		{r-}
  		Bold Red	{r+}
  		Green		{g-}
		Bold Green	{g+}
		Yellow		{y-}
		Bold Yellow	{y+}
		Blue		{b-}
		Bold Blue	{b+}
		Magenta 	{m-}
		Bold Magenta	{m+}
		Cyan		{c-}
		Bold Cyan	{c+}
		Reset		{w-}/{w+}  
