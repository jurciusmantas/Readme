namespace Readme.Model
{
    public interface IConnection
    {
        bool AskForReadme(string language, string project);
    }
}