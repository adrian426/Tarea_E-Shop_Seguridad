default:
	g++ -Wall -I/usr/include/cppconn -ologin login.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -ologout logout.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oHome Home.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -osign_up SignUp.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oadd_product AddProduct.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oadd_claim AddClaim.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oadd_to_cart AddToCart.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oreview_cart ReviewCart.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oremove_from_cart RemoveFromCart.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -oreview_claims ReviewClaims.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -ocheckout CheckoutCart.cpp -L/usr/lib -lmysqlcppconn
	g++ -Wall -I/usr/include/cppconn -ohistory BoughtHistory.cpp -L/usr/lib -lmysqlcppconn