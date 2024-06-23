bool isFileEmpty(const string fileName)
{
  ifstream file(fileName, ios::binary | ios::ate);
  return file.tellg() == 0;
}