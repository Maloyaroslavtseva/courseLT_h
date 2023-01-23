Action()
{
	lr_start_transaction("UC3_DeleteDooking");
	
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
	

	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Not_A Brand\";v=\"99\", \"Google Chrome\";v=\"109\", \"Chromium\";v=\"109\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("login");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",
		LAST);


	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(3);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("Itinerary");


	web_reg_find("SaveCount=noFlights",
		"Text=No flights have been reserved",
		LAST);

	web_reg_save_param("numFlightsBefore",
			"LB=A total of ",
			"RB= scheduled",
			LAST);
	
	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(6);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("Itinerary",LR_AUTO);
	
	// No flights have been reserved.
	lr_log_message("noFlights=%s", lr_eval_string("{noFlights}"));

    if (atoi(lr_eval_string("{noFlights}"))!=1) { // Есть бронь!
		

// способ не проходит, иногда возникает ошибка видимо из-за того что номера рейсов случайные
//	Action.c(177): Error -26368: "Text=flightID" value="0-0-{" found for web_reg_find (count=1)  	[MsgId: MERR-26368]
//		web_reg_save_param("flightID",
//		"LB=flightID\" value=\"",
//		"RB=\"",
//		LAST);
// 

   
        if (atoi(lr_eval_string("{numFlightsBefore}")) > 1 ) { // количество брони больше 1

			lr_start_transaction("delete");
			
		    web_reg_save_param("numFlightsAfter",
			"LB=A total of ",
			"RB= scheduled",
			LAST);
			
			
			
	//		web_reg_find("Fail=Found",
	//		"Text=flightID\" value=\"{flightID}",
	//		LAST);
	
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(5);
		
			web_submit_form("itinerary.pl", 
				"Snapshot=t4.inf", 
				ITEMDATA, 
				"Name=1", "Value=on", ENDITEM, 
		        "Name=removeFlights.x", "Value=61", ENDITEM,
				"Name=removeFlights.y", "Value=9", ENDITEM,
				LAST);
			
			
			if (atoi(lr_eval_string("{numFlightsBefore}"))-1 != atoi(lr_eval_string("{numFlightsAfter}"))) {
				lr_end_transaction("delete", LR_FAIL);		
			}
			else {
				lr_end_transaction("delete",LR_AUTO);
		    }
       } else { // количество брони 1
	
			lr_start_transaction("delete");
			
		
			web_reg_find("SaveCount=noFlightsAfter",
			"Text=No flights have been reserved",
			LAST);
			
	
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(6);
		
			web_submit_form("itinerary.pl", 
				"Snapshot=t4.inf", 
				ITEMDATA, 
				"Name=1", "Value=on", ENDITEM, 
		        "Name=removeFlights.x", "Value=61", ENDITEM,
				"Name=removeFlights.y", "Value=9", ENDITEM,
				LAST);
			
			
			if (atoi(lr_eval_string("{noFlightsAfter}")) != 1) {
				lr_end_transaction("delete", LR_FAIL);		
			}
			else {
				lr_end_transaction("delete",LR_AUTO);
		    }

        }
	} 
	else { // atoi(lr_eval_string("{noFlights}")) ==1 - удалять нечего
		
		lr_start_transaction("delete");
		lr_end_transaction("delete",LR_AUTO);
			
	}

	
	lr_start_transaction("logout");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome to the Web Tours site.",
		LAST);


	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(3);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t6.inf", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("UC3_DeleteDooking",LR_AUTO);
	
	return 0;
}