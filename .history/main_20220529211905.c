int main(int argc, const char *argv[])
{
  const char *c = "the string";
  char *start = &c[4];
  char *end = &c[7];
  // Note the + 1 here, to have a null terminated substring
  char *substr = (char *)calloc(1, end - start + 1);
  memcpy(substr, start, end - start);
  printf("%s\n", substr);
  return 0;
}