Action()
{

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

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(13);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value=jojo", ENDITEM, 
		"Name=password", "Value=bean", ENDITEM, 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("itinary");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(6);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("itinary",LR_AUTO);

	lr_start_transaction("delete");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(61);

	web_submit_form("itinerary.pl", 
		"Snapshot=t4.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=2", "Value=<OFF>", ENDITEM, 
		"Name=3", "Value=on", ENDITEM, 
		"Name=4", "Value=<OFF>", ENDITEM, 
		"Name=5", "Value=<OFF>", ENDITEM, 
		"Name=6", "Value=on", ENDITEM, 
		"Name=7", "Value=<OFF>", ENDITEM, 
		"Name=8", "Value=<OFF>", ENDITEM, 
		"Name=9", "Value=<OFF>", ENDITEM, 
		"Name=10", "Value=<OFF>", ENDITEM, 
		"Name=11", "Value=<OFF>", ENDITEM, 
		"Name=12", "Value=<OFF>", ENDITEM, 
		"Name=13", "Value=<OFF>", ENDITEM, 
		"Name=14", "Value=<OFF>", ENDITEM, 
		"Name=15", "Value=<OFF>", ENDITEM, 
		LAST);

	lr_end_transaction("delete",LR_AUTO);

	return 0;
}