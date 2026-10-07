#include "utils.h"
#include "mutex.h"

namespace utils
{
	uint32_t get_tick_count()
	{
	  struct timeval tv;
	  if (gettimeofday(&tv, NULL)) return 0;
	  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}

	FILE *log_file = NULL;

	void log(const char *fmt, ...)
	{
		CS_SCOPE(mutex::mlog);

		char str[256];
		va_list lst;
		va_start(lst, fmt);
		vsnprintf(str, sizeof(str), fmt, lst);
		va_end(lst);
		// Script and file names can contain %; never use them as formats.
		printf("%s", str);
		printf("\n");
		pspDebugScreenPrintf("%s", str);
		pspDebugScreenPrintf("\n");
		if (!log_file)
		{
			char str[] = "ms0:/PSP/PLUGINS/cleo/cleo.log";
			remove(str);
			log_file = fopen(str, "wt");
		}
		if (log_file)
		{
			struct timeval tv;
			struct timezone tz;
			memset(&tv, 0, sizeof(tv));
			memset(&tz, 0, sizeof(tz));
			if (gettimeofday(&tv, &tz) == 0)
			{			
				tv.tv_sec -= tz.tz_minuteswest * 60;
				uint32_t h1 = tv.tv_sec / 3600;
				uint32_t h = h1 % 24;
				uint32_t m = (tv.tv_sec % 3600) / 60;
				uint32_t s = tv.tv_sec - h1 * 3600 - m * 60;
				fprintf(log_file, "[%s%02d:%02d:%02d] ", tz.tz_minuteswest ? "" : "UTC|", int(h), int(m), int(s));
			}
			va_list lst;
			va_start(lst, fmt);
			vfprintf(log_file, fmt, lst);
			va_end(lst);			
			fprintf(log_file, "\n");
			fflush(log_file);
		}
	}

	bool string_compare(const std::string &left, const std::string &right)
	{
	   for (std::string::const_iterator lit = left.begin(), rit = right.begin(); lit != left.end() && rit != right.end(); ++lit, ++rit)
	      if (tolower(*lit) < tolower(*rit))
	         return true;
	      else if (tolower(*lit) > tolower(*rit))
	         return false;
	   if (left.size() < right.size())
	      return true;
	   return false;
	}

	bool list_files_in_dir(std::string dir, std::vector<std::string> &files)
	{
		int fd = sceIoDopen(dir.c_str());
		if (fd < 0) return false;
		SceIoDirent dirp;
		memset(&dirp, 0, sizeof(dirp));
		while (sceIoDread(fd, &dirp) > 0)
			if((dirp.d_stat.st_attr & FIO_SO_IFDIR) == 0)
				files.push_back(std::string(dirp.d_name));
		sceIoDclose(fd);
	    if (files.size())
	    	sort(files.begin(), files.end(), string_compare);
	    return true;
	}

	uint8_t *load_binary_file(std::string filename, uint32_t &size)
	{
		size=0;
		FILE* file=fopen(filename.c_str(),"rb");
		if (!file) return nullptr;
		if (fseek(file,0,SEEK_END)!=0) { fclose(file);return nullptr; }
		const long length=ftell(file);
		if (length<=0 || fseek(file,0,SEEK_SET)!=0) { fclose(file);return nullptr; }
		auto* buffer=cast<ptr>(malloc(static_cast<size_t>(length)));
		if (!buffer) { fclose(file);return nullptr; }
		const size_t read=fread(buffer,1,static_cast<size_t>(length),file);
		const bool valid=read==static_cast<size_t>(length) && !ferror(file);
		fclose(file);
		if (!valid) { free(buffer);return nullptr; }
		size=static_cast<uint32_t>(length);
		return buffer;
	}

}


