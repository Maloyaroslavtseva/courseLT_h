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
	
	
	
	lr_start_transaction("UC1_login_Logout");
	
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

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"108\", \"Google Chrome\";v=\"108\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_url("header.html", 
		"URL=http://localhost:1080/WebTours/header.html", 
		"Resource=0", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_sight", LR_AUTO);
	
	
	

	lr_start_transaction("login");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",
		LAST);


	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(6);

	web_submit_form("login.pl", 
		"Snapshot=t5.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);
	
	
	lr_start_transaction("find_flights");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(10);

	lr_save_datetime ("%m/%d/%Y", DATE_NOW, "pDate1");
 
	
	lr_save_datetime ("%m/%d/%Y", DATE_NOW+ONE_DAY*randNumber, "pDate2");
	


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
		
		
	

	lr_end_transaction("find_flights",LR_AUTO);

	lr_start_transaction("logout");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(3);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
    lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("UC1_login_Logout",LR_AUTO);

	return 0;
}