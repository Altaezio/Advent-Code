#pragma once

std::string sol7v1();
std::string sol7v2();

int evaluateHand(std::string hand);

bool compHand(std::tuple<std::string, int, int> a, std::tuple<std::string, int, int> b);

int cardToInt(char& c);

int evaluateHandJoker(std::string hand);

//bool compHandJoker(std::tuple<std::string, int, int> a, std::tuple<std::string, int, int> b);

int cardToIntJoker(char c);

//bool compCharInHand()
