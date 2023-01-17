Action()
{

	 int sufix = rand(); 
	 char buffer[50];
	 
	 	
    lr_start_transaction("UC7_UserRegistration");	
    
    sprintf(buffer, "A%d", sufix);
	lr_save_string(buffer, "login");
	
	lr_log_message("login=%s", buffer);
    	
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
	
	 // web_reg_find("Fail=NotFound","Text/IC=Thank you, <b>{login}</b>",LAST);
	 
	 web_reg_find("SaveCount=reg",
		"Text=Thank you, <b>{login}</b>",
		LAST);
	 
	 web_reg_find("SaveCount=taken",
		"Text=Your username is taken",
		LAST);

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

	if (atoi(lr_eval_string("{reg}"))!=1) {
		if (atoi(lr_eval_string("{taken}"))!=1) {
			lr_end_transaction("registering", LR_FAIL);
		}
		else {
			lr_end_transaction("registering",LR_AUTO);
		}
		
	}
	else {
		lr_end_transaction("registering",LR_AUTO);
	}
	
	lr_end_transaction("UC7_UserRegistration",LR_AUTO);

	return 0;
}