Action()
{
	
	int cities_size = 10; // размер массива городов
	
	// массив городов
	static char* cities[10] = {
    	"Denver",
        "Frankfurt",
        "London",
        "Los Angeles",
        "Paris",
        "Portland",
        "San Francisco",
        "Seattle",
        "Sydney",
        "Zurich" };

    
	int randNumber, //  
	idep, // индекс города отправления
	iarr; // индекс грода прибытия
	
	
    lr_start_transaction("UC5_flihtSelection");
	
	randNumber = rand()%30 + 1;  //Generate Random Number between 1 to 30
	idep = rand()%cities_size; // выбор случайгоно числа от 0 до 9
	iarr = rand()%cities_size; // выбор случайгоно числа от 0 до 9
	while(idep == iarr ) {         // пока индексы не станут разными 
    	iarr = rand()%cities_size; // изменяем индекс города прибытия
	}
	
	lr_save_string(cities[idep], "depart"); // в параметр depart сохраняем город отправления согласно выбранному индексу
    lr_save_string(cities[iarr], "arrive"); // в параметр arrive сохраняем город прибытия согласно выбранному индексу
    
    
	
    lr_start_transaction("open_sight");
    
    web_reg_find("Fail=NotFound",
		"Text/IC=Welcome to the Web Tours site.",
		LAST);
	
	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"108\", \"Google Chrome\";v=\"108\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

/*Correlation comment - Do not change!  Original value='135437.136654516zQzzftHpHVzzzzzHtVHQQpcizD' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_sight",LR_AUTO);
	
	

	lr_start_transaction("login");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",
		LAST);


	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(47);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=43", ENDITEM,
		"Name=login.y", "Value=10", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);
	
	

	lr_start_transaction("flights");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Departure City",
		LAST);


	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(70);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("flights",LR_AUTO);

	lr_start_transaction("find_flights");
	
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Flight departing from",
		LAST);

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(104);

	lr_save_datetime ("%m/%d/%Y", DATE_NOW, "pDate1");
 
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW+ONE_DAY*randNumber, "pDate2");
	

	web_reg_save_param("outboundFlight",
		"LB=outboundFlight\" value=\"",
		"RB=\"",
		"Ord=ALL",
		LAST);


	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value=", ENDITEM, 
		"Name=departDate", "Value={pDate1}", ENDITEM, 
		"Name=arrive", "Value=", ENDITEM, 
		"Name=returnDate", "Value={pDate2}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=43", ENDITEM, 
		"Name=findFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
		
		
    lr_save_string(lr_paramarr_random("outboundFlight"), "outboundFlight");

	

	lr_end_transaction("find_flights",LR_AUTO);

	lr_think_time(95);

	lr_start_transaction("flight_selection");

	web_reg_find("Fail=NotFound",
		"Text/IC=First Name",
		LAST);
	
	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=43", ENDITEM, 
		"Name=reserveFlights.y", "Value=7", ENDITEM, 
		LAST);

	lr_end_transaction("flight_selection",LR_AUTO);
	
	lr_end_transaction("UC5_flihtSelection",LR_AUTO);
	

	return 0;
}
