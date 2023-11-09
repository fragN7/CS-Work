
namespace RayTracer
{
    public class Sphere : Geometry
    {
        private Vector Center { get; set; }
        private double Radius { get; set; }

        public Sphere(Vector center, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            Radius = radius;
        }

        public Vector GetCenter()
        {
            return Center;
        }
        
        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            var timeClosest = (Center - line.X0) * line.Dx;
            var pointAfterTime = line.CoordinateToPosition(timeClosest);
            var lengthCenterAndPoint = (Center - pointAfterTime).Length();
            var distanceInPoints = Math.Sqrt(Radius * Radius - lengthCenterAndPoint * lengthCenterAndPoint);

            if (timeClosest > minDist && timeClosest < maxDist && lengthCenterAndPoint <= Radius)
            {
                var firstIntersection = timeClosest - distanceInPoints;
                return new Intersection(true, true, this, line, firstIntersection);
            }
            
            return new Intersection();
        }

        public override Vector Normal(Vector v)
        {
            var n = v - Center;
            n.Normalize();
            return n;
        }
    }
}