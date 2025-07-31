/* Does gcc pad structures */

struct xyz {
	short aa;
	int bb;
	short cc;
	short dd;
	struct xyz *next;
};

struct xyz	*p;

void
check ( void )
{
		int i1, i2, i3;

		p = (struct xyz *) 0;

		i1 = sizeof(struct xyz);
		i2 = (int) &(p->cc);
		i3 = (int) &(p->next);
}
