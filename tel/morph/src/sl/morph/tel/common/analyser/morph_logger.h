#define	PRINT_LOG(log_file, message)	\
		{								\
			print_log(log_file, 		\
						message, 		\
						program_name,	\
						__FILE__, 		\
						__LINE__,		\
						FUNCTION);		\
		}								



#define	PRINT_ERR(log_file, message)	\
		{								\
			print_err(log_file, 		\
				message,				\
				program_name);			\
		}								
