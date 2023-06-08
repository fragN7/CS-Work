using Lab10_Dotnet.Data;

namespace Lab10_Dotnet.Validation;

public class Validator
{
    public string validate(Multimedia file)
    {
        var err = "";

        if (file.Title == string.Empty)
        {
            err += "Title is empty";
        }
        
        if (file.Format == string.Empty)
        {
            err += "Format is empty";
        }
        
        if (file.Genre == string.Empty)
        {
            err += "Genre is empty";
        }

        if (file.Path == string.Empty)
        {
            err += "Path is empty";
        }

        if (string.IsNullOrEmpty(file.Path)) return err;
        var dotPosition = file.Path.LastIndexOf('.');
        if (dotPosition != -1)
        {
            var substringAfterDot = file.Path.Substring(dotPosition + 1);

            if (substringAfterDot != file.Format)
            {
                err += "The format does not match the file extension in the path.";
            }
        }
        else
        {
            err += "Invalid path.";
        }

        return err;
    }
}