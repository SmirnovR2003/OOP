#pragma once

#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};


class CHttpUrl
{
public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
	// �� ������ ����������
	std::string GetURL()const;

	// ���������� �������� ���
	std::string GetDomain()const;

	/*
		���������� ��� ���������. �������:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument()const;

	// ���������� ��� ���������
	Protocol GetProtocol()const;

	// ���������� ����� �����
	unsigned short GetPort()const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol = Protocol::HTTP;
	unsigned short m_port = 0;
};


