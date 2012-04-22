let true <
	case '!' \cust: send cust (false) ;

    case '&&' true \cust: send cust (true) ;
    case '&&' \val \cust: send cust (false) ;

	case '||' \val \cust: send cust (true) ;
>

let false <
	case '!' \cust: send cust (true) ;
	
	case '&&' \val \cust: send cust (false) ;
	
	case '||' true \cust: send cust (true) ;
	case '||' \val \cust: send cust (false) ;
>