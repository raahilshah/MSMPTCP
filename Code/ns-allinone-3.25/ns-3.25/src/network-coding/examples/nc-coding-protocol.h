/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */

// This class declares the API for an Application Layer implementation 
// of network coding using Random Linear Network Coding

#pragma once

#define DATA_BUFSIZE 409600

#include <kodocpp/kodocpp.hpp>

class NetworkCodingProtocol
{
public:

	NetworkCodingProtocol (const ns3::Ptr<ns3::Socket> socket, const std::string fieldStr,
		const uint32_t generationSize, const uint32_t packetSize);

	void SendData (std::vector<uint8_t> *data, int dataSize);

	void SendPacket (ns3::Ptr<ns3::Packet> packet);

	void Send ();

	void Receive (ns3::Ptr<ns3::Socket> socket);

	bool DecodingComplete ();

	void GetDecodedBlock (std::vector<uint8_t> *data);

private:

	/**
	* Lower layer socket
	*/
	const ns3::Ptr<ns3::Socket> m_socket;

	/**
	* Random Linear Coding Parameters
	*/
	// Galois field for random coefficient selection
	// String representation: "binary", "binary4", "binary8"
	const std::string m_fieldStr;
	// Coding block/generation size
	const uint32_t m_genSize;
	// Packet size in bytes
	const uint32_t m_packSize;

	/**
	* Coding layer objects
	*/
	kodocpp::encoder m_encoder;
	std::vector<uint8_t> m_encoderBuffer;
	int m_bufferedPackets;
	std::vector<uint8_t> m_payload;
	kodocpp::decoder m_decoder;
	std::vector<uint8_t> m_decoderBuffer;

	/** 
	* Counters
	*/
	int m_sentCount;
	int m_recvdCount;

	/** Sending data
	*/
	std::vector<uint8_t> *m_data;
	int m_dataSize;
	int m_dataIndex;

	/**
	* Helper functions
	*/
	void ReadyNextDataBlock ();

};