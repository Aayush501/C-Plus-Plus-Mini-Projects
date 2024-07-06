#include <iostream>
#include <string>
#include <cpprest/http_client.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
	// Banner:
	cout << "-------------------------------------\n";
	cout << "     My Currency Converter App\n";
	cout << "-------------------------------------\n";

	// Taking Inputs of From, To, and Amount as:
	string amount, fromCurrency, toCurrency;
	cout << "Convert Currency From: ";
	cin >> fromCurrency;
	cout << "Convert to: ";
	cin >> toCurrency;
	cout << "Enter Amount: ";
	cin >> amount;
	
	// Adding API: 
	http_client client(U("https://api.apilayer.com/exchangerates_data"));
	uri_builder builder(U("/convert"));

	builder.append_query(U("from"), utility::conversions::to_string_t(fromCurrency));
	builder.append_query(U("to"), utility::conversions::to_string_t(toCurrency));
	builder.append_query(U("amount"), utility::conversions::to_string_t(amount));
	builder.append_query(U("apikey"), U(""));

	// Sending Request and Getting Response:
	http_request request(methods::GET);
	request.set_request_uri(builder.to_string());

	client.request(request).then([](http_response response) {
		return response.extract_json();
		}).then([](web::json::value body) {
			cout << "Conversion Date: " << utility::conversions::to_utf8string(body[U("date")].as_string()) << endl;
			cout << "Conversion Rate: " << body[U("info")][U("rate")].as_double() << " " << utility::conversions::to_utf8string(body[U("query")][U("to")].as_string()) << "/" << utility::conversions::to_utf8string(body[U("query")][U("from")].as_string()) << endl;
			cout << "Conversion Result: \n";
			cout << body[U("query")][U("amount")].as_double() << " " << utility::conversions::to_utf8string(body[U("query")][U("from")].as_string()) << " = ";
			cout << body[U("result")].as_double() << " " << utility::conversions::to_utf8string(body[U("query")][U("to")].as_string()) << endl;
			}).wait();
	return 0;
}