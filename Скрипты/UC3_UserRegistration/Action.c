Action()
{

	
	OpenSight();
	
	
	lr_start_transaction("sign_up_now");
	
	
    web_reg_find("Fail=NotFound","Text/IC=First time registering",LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(37);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("sign_up_now",LR_AUTO);
	
	
	

	lr_start_transaction("registering");
	
	 web_reg_find("Fail=NotFound","Text/IC=Thank you, <b>{login}</b>",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(112);

	web_submit_form("login.pl_2", 
		"Snapshot=t8.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=44", ENDITEM, 
		"Name=register.y", "Value=7", ENDITEM, 
		LAST);

	lr_end_transaction("registering",LR_AUTO);

	return 0;
}